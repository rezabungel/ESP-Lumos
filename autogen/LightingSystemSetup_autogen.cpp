// ============================================================
//  THIS FILE IS AUTO-GENERATED
//  Generated from house configuration: house_config.yaml
//  SHA256 hash of source config: 4180650cd0458f6d22ae02a79c5f4cb23b0a4fb610d9611398084bd111cdb209
//  Do not modify manually, your changes will be overwritten.
// ============================================================

#include "LightingSystemSetup.h"

// ============================================================
//  OBJECTS INITIALIZATION
//  Instantiate all objects: House, Room, LightGroup, Strip
// ============================================================
House myHouse("myHouse");
Room room_599513459b94f5b7287c47f8266cd787("kitchen");
LightGroup lightgroup_c3225407148bbbd1cec05ba40f99706e("floor");
Strip<46> strip_10a1639c71eebb726b8a9e05a765cefb("Strip-1", 300);
Strip<48> strip_c5a86d32bf81a66c1b6e8b0735c5a349("Strip-2", 300);
Room room_5435c78cfabe01003b9b5ba94f7ca8e1("livingRoom");
LightGroup lightgroup_589dbf55ee8d2f5f9848f5174243d7bd("floor");
Strip<47> strip_bb0c8f92b9c6a4813456399ad5e56a81("Strip-1", 300);

// ============================================================
//  LED MANAGER INITIALIZATION
//  Create LED manager instance
// ============================================================
LedManager ledManager;

void setupLightingSystem()
{
    // ========================================================
    // HOUSE HIERARCHY BUILD
    // Build hierarchy: House -> Room -> LightGroup -> Strip
    // ========================================================
    myHouse.addElement(&room_599513459b94f5b7287c47f8266cd787);
    room_599513459b94f5b7287c47f8266cd787.addElement(&lightgroup_c3225407148bbbd1cec05ba40f99706e);
    lightgroup_c3225407148bbbd1cec05ba40f99706e.addElement(&strip_10a1639c71eebb726b8a9e05a765cefb);
    lightgroup_c3225407148bbbd1cec05ba40f99706e.addElement(&strip_c5a86d32bf81a66c1b6e8b0735c5a349);
    myHouse.addElement(&room_5435c78cfabe01003b9b5ba94f7ca8e1);
    room_5435c78cfabe01003b9b5ba94f7ca8e1.addElement(&lightgroup_589dbf55ee8d2f5f9848f5174243d7bd);
    lightgroup_589dbf55ee8d2f5f9848f5174243d7bd.addElement(&strip_bb0c8f92b9c6a4813456399ad5e56a81);

    // ========================================================
    // LED MANAGER REGISTRATION
    // Register all strips in LED manager
    // ========================================================
    ledManager.addStrip(&strip_10a1639c71eebb726b8a9e05a765cefb);
    ledManager.addStrip(&strip_c5a86d32bf81a66c1b6e8b0735c5a349);
    ledManager.addStrip(&strip_bb0c8f92b9c6a4813456399ad5e56a81);
}
