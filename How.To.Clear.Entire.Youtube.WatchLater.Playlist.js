// javascript
let i = -1;
function deleteWL(){
    let next_element = setInterval(function(){
        try{
            const css_button = "css-selector-path-to-menu";
            const css_selector = "css-selector-path-to-menu-option";
            // Now convert the result to a jQuery object
            let button = $(css_button);
            let elem = $(css_selector);
            // Now you can manipulate el using jQuery, for example:
            button.click(); // summon context menu
            elem.click(); // remove video
            console.log(`video ${++i} deleted`);
        } catch(e) {
            clearInterval(next_element);
        }
    },false);
}
deleteWL();
