import os
import hashlib
from dataclasses import dataclass, field
from typing import Any, Type, TypeVar

from jinja2 import Environment, FileSystemLoader
import yaml


T = TypeVar('T')

@dataclass
class Strip:
    name: str
    pin: int
    length: int
    base_cpp_var_name: str = field(init=False, default="strip")

    def __post_init__(self):
        self.name = self.name.replace(' ', '-')

    def get_child_elements(self) -> None:
        return None

@dataclass
class LightGroup:
    name: str
    strips: list[Strip]
    base_cpp_var_name: str = field(init=False, default="lightGroup")

    def __post_init__(self):
        self.name = self.name.replace(' ', '-')
        for i in range(len(self.strips)):
            self.strips[i] = Strip(**self.strips[i])

    def get_child_elements(self) -> list[Strip]:
        return self.strips

@dataclass
class Room:
    name: str
    light_groups: list[LightGroup]
    base_cpp_var_name: str = field(init=False, default="room")

    def __post_init__(self):
        self.name = self.name.replace(' ', '-')
        for i in range(len(self.light_groups)):
            self.light_groups[i] = LightGroup(**self.light_groups[i])

    def get_child_elements(self) -> list[LightGroup]:
        return self.light_groups

@dataclass
class House:
    name: str
    rooms: list[Room]
    cpp_var_name: str = field(init=False, default="house")

    def __post_init__(self):
        self.name = self.name.replace(' ', '-')
        for i in range(len(self.rooms)):
            self.rooms[i] = Room(**self.rooms[i])

    def get_child_elements(self) -> list[Room]:
        return self.rooms

    def get_cpp_initialization(self) -> str:
        return generate_cpp_initialization(cpp_class=self.__class__.__name__,
                                            object_name = self.name,
                                            object_path = self.name,
                                            base_cpp_var_name = None,
                                            child_elements=self.rooms,
                                            pin = None,
                                            length = None)

@dataclass
class HouseConfig:
    house: House

    def __post_init__(self):
        self.house=House(**self.house)

    def get_cpp_initialization(self) -> str:
        return self.house.get_cpp_initialization()


def get_config_path(config_file_name: str) -> str:
    current_dir = os.path.dirname(__file__)
    config_path = os.path.join(current_dir, ".." , "data", "config", config_file_name)
    return os.path.abspath(config_path)

def load_config_from_yaml(config_file_name: str, config_structure: Type[T]) -> T:
    config_file_path = get_config_path(config_file_name)
    with open(config_file_path, 'r', encoding='utf-8') as config:
        config_dict = yaml.safe_load(config)

    return config_structure(**config_dict)

def generate_cpp_initialization(cpp_class: str, object_name: str, object_path: str,
                                base_cpp_var_name: str | None, child_elements: list[T] | None,
                                pin: int | None, length: int | None) -> str:
    cpp_code: list[str] = []

    if base_cpp_var_name is None:
        cpp_var_name = f"{object_name}"
    else:
        object_path = f"{object_path}/{object_name}"
        md5_object_path = compute_md5_from_string(object_path)
        cpp_var_name = f"{base_cpp_var_name}_{md5_object_path}"

    if None in (pin, length):
        cpp_line = f'{cpp_class} {cpp_var_name}("{object_name}");'
    else:
        cpp_line = f'{cpp_class}<{pin}> {cpp_var_name}("{object_name}", {length});'

    cpp_code.append(cpp_line)

    if child_elements is not None:
        for child_element in child_elements:
            cpp_code.append(generate_cpp_initialization(cpp_class=type(child_element).__name__,
                                                        object_name = child_element.name,
                                                        object_path = object_path,
                                                        base_cpp_var_name = type(child_element).__name__.lower(),
                                                        child_elements=child_element.get_child_elements(),
                                                        pin=getattr(child_element, "pin", None),
                                                        length=getattr(child_element, "length", None)))

    return '\n'.join(cpp_code)

def generate_cpp_led_manager_initialization() -> str:
    return f"LedManager ledManager;"

def generate_cpp_add_element(parent_var_name: str, child_var_name: str) -> str:
    return f"{parent_var_name}.addElement(&{child_var_name});"

def generate_cpp_hierarchy(cpp_initialization: str) -> str:
    cpp_code: list[str] = []
    house_index = 0
    room_index = 0
    light_group_index = 0

    cpp_init_lines = cpp_initialization.split(';')[:-1]
    cpp_var_names = [cpp_init_line.split()[1].split('(')[0] for cpp_init_line in cpp_init_lines]

    for i in range(len(cpp_var_names)):
        if 'myHouse' in cpp_var_names[i]:
            house_index = i
            continue
        if 'room' in cpp_var_names[i]:
            room_index = i
            cpp_code.append(generate_cpp_add_element(cpp_var_names[house_index], cpp_var_names[room_index]))
            continue
        if 'lightgroup' in cpp_var_names[i]:
            light_group_index = i
            cpp_code.append(generate_cpp_add_element(cpp_var_names[room_index], cpp_var_names[light_group_index]))
            continue

        cpp_code.append(generate_cpp_add_element(cpp_var_names[light_group_index], cpp_var_names[i]))

    return '\n'.join(cpp_code)

def generate_cpp_led_manager_registration (cpp_led_manager_initialization: str, cpp_initialization: str) -> str:
    cpp_code: list[str] = []

    cpp_led_manager_name = cpp_led_manager_initialization.replace(';', ' ').split()[1]
    cpp_init_lines = cpp_initialization.split(';')[:-1]
    cpp_var_names = [cpp_init_line.split()[1].split('(')[0] for cpp_init_line in cpp_init_lines]

    for cpp_var_name in cpp_var_names:
        if 'strip' in cpp_var_name:
            cpp_code.append(f'{cpp_led_manager_name}.addStrip(&{cpp_var_name});')
    
    return '\n'.join(cpp_code)

def render_template_jinja2(tamplate_path: str, tamplate_name: str, render_context: dict[str, Any]) -> str:
    env = Environment(loader=FileSystemLoader(tamplate_path))
    tm = env.get_template(tamplate_name)
    return tm.render(render_context)

def compute_md5_from_string(value: str) -> str:
    return hashlib.md5(value.encode('utf-8')).hexdigest()

def compute_sha256_from_file(file_path: str) -> str:
    h = hashlib.sha256()

    with open(file_path, 'rb') as file:
        while True:
            chunk = file.read(65536) 
            if not chunk:
                break
            h.update(chunk)

    return h.hexdigest()

def save_file(file_path: str, file_name: str, content: str) -> None:
    with open(f'{file_path}/{file_name}', 'w', encoding='utf-8') as f:
        f.write(content)

if __name__ == "__main__":
    current_dir: str = os.path.dirname(__file__)

    config_file_name: str = "house_config.yaml"
    config_file_path: str = os.path.join(current_dir, ".." , "data", "config", config_file_name)
    config_file_sha256: str = compute_sha256_from_file(config_file_path)

    house_config = load_config_from_yaml(config_file_name, HouseConfig)

    init_code = house_config.get_cpp_initialization()
    hierarchy_code = generate_cpp_hierarchy(init_code)
    led_manager_init = generate_cpp_led_manager_initialization()
    led_manager_registration = generate_cpp_led_manager_registration(led_manager_init, init_code)

    render_context = {
        'config_file_name': config_file_name,
        'CONFIG_SHA256': config_file_sha256,
        'objects_init': init_code,
        'led_manager_init': led_manager_init,
        'hierarchy_build': hierarchy_code,
        'led_manager_registration': led_manager_registration
    }

    generated_cpp = render_template_jinja2('templates', 'LightingSystemSetup_autogen.cpp.j2', render_context)
    save_file('autogen', 'LightingSystemSetup_autogen.cpp', generated_cpp)
