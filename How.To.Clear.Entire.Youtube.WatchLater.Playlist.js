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

/*
Example

    // javascript
    let i = -1;
    function deleteWL(){
        let next_element = setInterval(function(){
            try {
                const css_button = "html body ytd-app div#content.style-scope.ytd-app ytd-page-manager#page-manager.style-scope.ytd-app ytd-browse.style-scope.ytd-page-manager ytd-two-column-browse-results-renderer.style-scope.ytd-browse.grid.grid-disabled div#primary.style-scope.ytd-two-column-browse-results-renderer ytd-section-list-renderer.style-scope.ytd-two-column-browse-results-renderer div#contents.style-scope.ytd-section-list-renderer ytd-item-section-renderer.style-scope.ytd-section-list-renderer div#contents.style-scope.ytd-item-section-renderer ytd-playlist-video-list-renderer.style-scope.ytd-item-section-renderer div#contents.style-scope.ytd-playlist-video-list-renderer ytd-playlist-video-renderer.style-scope.ytd-playlist-video-list-renderer div#menu.style-scope.ytd-playlist-video-renderer ytd-menu-renderer.style-scope.ytd-playlist-video-renderer yt-icon-button#button.dropdown-trigger.style-scope.ytd-menu-renderer button#button.style-scope.yt-icon-button yt-icon.style-scope.ytd-menu-renderer yt-icon-shape.style-scope.yt-icon icon-shape.yt-spec-icon-shape div";
                const css_selector = "ytd-menu-service-item-renderer.style-scope:nth-child(3)";
                // Now convert the result to a jQuery object
                let button = $(css_button);
                let elem = $(css_selector);
                // Now you can manipulate el using jQuery, for example:
                button.click(); // summon context menu
                elem.click(); // remove video
                console.log(`video ${++i} deleted`);
            } catch(e) {
                //clearInterval(next_element);
            }
        },false);
    }
    deleteWL();
*/
