<?php

/**
 * @file
 * Code for the project blocks.
 */

/**
 * Callback for the c4m_block_create_organisation block.
 */
function _c4m_content_organisation_block_c4m_block_create_organisation() {
  global $user;
  $markup = '';

  $markup = '';
  if ($user->uid) {
    if (user_access('create organisation content')) {
      $markup = l(
        t('Create an event site'),
        'node/add/event-site',
        array('attributes' => array('class' => array('btn', 'btn-primary')))
      );
    }
  }
  else {
    $markup = t(
      '!register or !login to create or join event sites',
      array(
        '!register' => l(t('Register'), 'user/register'),
        '!login' => l(
          t('log in'),
          'user/login',
          array(
            'query' => array('destination' => request_path()),
          )
        ),
      )
    );
  }
  return array(
    'subject' => '',
    'content' => $markup,
  );
}

/**
 * Organisation Dashboard title redesign.
 *
 * The function handles header title redesign project page.
 */
function _c4m_content_organisation_block_header_name_banner_organisation() {
  // First establish the current project.
  $project = c4m_og_current_group();
  $wrapper = entity_metadata_wrapper('node', $project);
  $markup = '';

  $title = $wrapper->title->value();

  $tagline = $wrapper->c4m_project_tag_line->value();

  $status = isset($wrapper->c4m_og_status) ? $wrapper->c4m_og_status->value(
  ) : 'published';

  $label_type = ($status == 'pending') ? "label-danger" : "label-default";

  $variables = [
    'title' => check_plain($title),
    'tagline' => check_plain($tagline),
    'type' => $project->type,
    'status' => $status,
    'label_type' => $label_type,
  ];
  $markup .= theme('c4m_content_organisation_header_title', $variables);

  // Adding AJAX for notification toggle, which is part of this block.
  drupal_add_library('system', 'drupal.ajax');

  return array(
    'subject' => '',
    'content' => $markup,
  );
}


/**
 * Callback for the c4m_block_organisation_about block.
 */
function _c4m_content_organisation_block_c4m_block_organisation_about() {
  $block = array();
  $block['subject'] = '';

  if ($node = c4m_og_current_group()) {
    // Render it with our custom group_dashboard view mode.
    $node_view = node_view($node, 'group_dashboard');
    $block['content'] = drupal_render($node_view);
  }

  return $block;
}

/**
 * Callback for the c4m_block_organisation_as Activity Stream block.
 */
function _c4m_content_organisation_block_c4m_block_organisation_as() {
  $block = array();

  $request = array(
    'group' => c4m_og_current_group()->nid,
    'html' => TRUE,
    // Sort the activity stream by timestamp descending.
    'sort' => '-timestamp',
    'hide_articles' => 1,
    'group_context' => TRUE,
  );

  $activities = c4m_message_get_activities($request);
  // Pass info via Drupal.settings.
  $settings['c4m'] = [
    'csrfToken' => drupal_get_token(\RestfulInterface::TOKEN_VALUE),
    'activities' => $activities,
    'data' => [
      'request' => $request,
      'entity' => ['group' => c4m_og_current_group()->nid],
    ],
  ];
  drupal_add_js($settings, 'setting');
  $block['content'] = theme('c4m_message_activity_stream');
  $block['content'] .= views_embed_view('group_activity_stream');

  return $block;
}