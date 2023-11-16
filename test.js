while (true) {
    var element = document.querySelector("div[class='tfny-circleGreen']");
    if (element !== null) {
        element.dispatchEvent(new MouseEvent("mousedown"));
        element.dispatchEvent(new MouseEvent("mouseup"));
    }
    await new Promise(resolve => setTimeout(resolve, 1));
}

while (true) {
    var element = document.querySelector("button[id='clicker']");
    if (element !== null) {
        element.dispatchEvent(new MouseEvent("mousedown"));
        element.dispatchEvent(new MouseEvent("mouseup"));
    }
    await new Promise(resolve => setTimeout(resolve, 1));
}