//@license magnet:?xt=urn:btih:0b31508aeb0634b347b8270c7bee4d411b5d4109&dn=agpl-3.0.txt AGPL-v3

/**
 * When the user changes the language via the language drop down, redirect the user to the relevant translation.
 */
(function() {
    var chooser = document.getElementById('language-chooser-select');
    // Fallback to English if none is selected
    var activeLang = 'en';
    for (var i = 0; i < chooser.children.length; i++) {
        if (chooser.children[i].selected) {
            activeLang = chooser.children[i].value;
       }
    }

    chooser.onchange = function() {
        var lang = this.value;
        var pageUrl = document.location.pathname;

        /*
         * If we are already on "/fr" and select "ES", we don't want to redirect to "/fr/es".
         * The apache docs website achieves this via AliasMatch in their apache config, but that
         * is not able to go into the .htaccess file and so makes the deployment of the site more
         * difficult. This solves the problem in JavaScript.
         */
        if (new RegExp('^/' + activeLang + '/').test(pageUrl)) {
            pageUrl = pageUrl.substring(activeLang.length + 1);
        }

        document.location = '' + '/' + lang + pageUrl;
    }
})();
// @license-end

