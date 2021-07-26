<?php

function better_search_admin_form() {
  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Better Search Text Options'),
  );
  
  $form['text']['placeholder_text'] = array(
    '#type' => 'textfield', 
    '#title' => t('Placeholder Text'),
    '#description' => t('Enter the text to be displayed in the search field (placeholder text)'),
    '#default_value' => variable_get('placeholder_text', 'search'),
    '#size' => 30, 
    '#maxlength' => 60,
    '#required' => TRUE,
  );
    
  $form['theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Better Search Theme Options'),
  );
  
  $options = array(
    0 => t('Background Fade'),
    1 => t('Expand on Hover'),
    2 => t('Expand Icon on Hover'),
    3 => t('Slide Icon on Hover'),
  );
  
  $form['theme']['theme'] = array(
    '#type' => 'radios',
    '#title' => t('Select Theme'),
    '#default_value' => variable_get('theme', 0),
    '#options' => $options,
    '#description' => t('Select the theme to use for the search block.'),    
  );
  
  $options = array(
    10 => '10',
    12 => '12',
    14 => '14',
    16 => '16',
    18 => '18',
    20 => '20',
    22 => '22',
    24 => '24',
    26 => '26',
    28 => '28',
    30 => '30',
  );
  
  $form['theme']['size'] = array(
    '#type' => 'select', 
    '#title' => t('Search Box Size'), 
    '#default_value' => variable_get('size', 20),
    '#options' => $options,
  );

  return system_settings_form($form);

}