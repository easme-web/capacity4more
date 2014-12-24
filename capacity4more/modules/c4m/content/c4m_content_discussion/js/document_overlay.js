(function ($) {

  $(document).bind('drupalOverlayLoad', function() {
  });

  $(document).on('click', function(event) {
    var $target = $(event.target);
    if ($target.is('a')) {
      var target = $target[0];
      var parents = $target.parents();
      var elements = [];
      $.each(parents, function(index, value) {
        var id = value.id;

        if (id.indexOf('node-') != -1 && id.match(/[0-9]/g)) {
          elements.push(value);
        }
      });

      elements.reverse();

      var nid = elements[0].id.replace(/\D/g, '');
      console.log(elements[0]);
      console.log($('#' + elements[0].id, window.document).find('[property="dc:title"]'));

      var title = $('#' + elements[0].id, window.document).find('[property="dc:title"]')[0];

      var $title = $(title);
      var label = $title.attr('content') ? $title.attr('content') : 'Property title is not found';

      $('#edit-c4m-related-document-und-0-target-id', parent.window.document).val(label + ' (' + nid + ')');
      parent.Drupal.overlay.close();
    }


  });

})(jQuery);
