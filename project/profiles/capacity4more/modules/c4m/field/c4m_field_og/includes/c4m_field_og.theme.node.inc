<?php

/**
 * @file
 * Custom Display Suite function fields.
 */

/**
 * DS field callback for Group name field.
 *
 * Renders a link to the group the current group node belongs to.
 *
 * @param array $field
 *   Field settings and information about the entity it’s being rendered on.
 *
 * @return mixed
 *   A string with a HTML link to the node's group or NULL if not a group node.
 */
function theme_c4m_field_og_group(array $field) {
  if (empty($field['entity'])) {
    return;
  }

  $entity = $field['entity'];

  if ($entity->entity_type === 'node') {
    // Don't show this field in a group context.
    $context = og_context();
    if ($context && $entity->type !== "share") {
      return;
    }
  }
  elseif (($entity->entity_type === 'comment')) {
    // If this is a comment, get the node of the comment.
    if (isset($entity->node_type)) {
      $entity = node_load($entity->nid);
    }
  }

  // Only show this field for group node types.
  if (!og_is_group_content_type('node', $entity->type)) {
    return;
  }

  // Get group node.
  $groups = og_get_entity_groups('node', $entity);

  // Only show this field for group nodes.
  if (!isset($groups['node'])) {
    return;
  }

  $group_nid = array_pop($groups['node']);
  $group = node_load($group_nid);

  $uri_info = entity_uri('node', $group);

  c4m_og_purl_alter_uri_info_purl_dashboard($uri_info);

  $group_type = $group->type;

  if ($group->type == 'project') {
    $entity = entity_metadata_wrapper('node', $group);
    $group_type = $entity->c4m_project_type->value();
  }
  if ($group->type == 'event_site') {
    $entity = entity_metadata_wrapper('node', $group);
    $group_type = 'Event site';
  }
  if ($group->type == 'organisation') {
    $entity = entity_metadata_wrapper('node', $group);
    $group_type = 'Organisation';
  }

  // Return a link to the group dashboard.
  $output = l($group->title, $uri_info['path'], $uri_info['options']);
  if (!empty($field['formatter_settings']['show_group_type'])) {
    $output = ucfirst($group_type) . ': ' . $output;
  }

  return $output;
}
