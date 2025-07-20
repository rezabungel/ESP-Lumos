function increment() {
    const upDiv = document.querySelector('.up');
    let current = parseInt(upDiv.textContent, 10);
    upDiv.textContent = current + 1;
}
