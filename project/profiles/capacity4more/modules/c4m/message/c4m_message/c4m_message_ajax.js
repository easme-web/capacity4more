/**
 * @file
 * Load activity stream via Ajax.
 */

(function ($) {
    "use strict";

    /**
     * Load remote content after the main page loaded.
     */
    Drupal.behaviors.my_module_load_remote_content = {
        attach: function (context, settings) {
            $("#activity-wrapper").once("activity-wrapper", function () {

                var base = $(this).attr("id");

                var element_settings = {
                    url: window.location.protocol + "//" + window.location.hostname + settings.basePath + settings.pathPrefix + "ajax/remote",
                    event: "click",
                    progress: {
                        type: "throbber"
                    }
                };
                Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
                $(this).click();
            });

            // When Ajax returns successfully, initiate the activity stream (Angular) controller.
            $(document).ajaxComplete(function (event, response, settings) {

                var responses = JSON.parse(response.responseText);

                responses.forEach(function (response) {
                    if ("selector" in response) {
                        if (response.selector === "#activity-wrapper") {
                            angular.bootstrap(document.getElementsByTagName("html")[0], ["c4mApp"]);
                        }
                    }
                });

            });
        }
    };

})
(jQuery);
