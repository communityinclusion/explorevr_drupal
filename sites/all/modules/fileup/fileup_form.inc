<?php

/**
 * @file
 */
function fileup_message() {
  return t('Use the field below to upload an archive file (.zip only) containing images.  The images will be extracted and available on the Image downloads page.');
}

////////////////  Upload Form //////////////////////

function fileup_upload_form($form_state) {

  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('Archive file'),
    '#description' => t('Upload an archive (.zip) file containing files with the following extensions: jpg, jpeg, png, gif, tif, tiff, bmp'),
  );
  $form['foldername'] = array(
      '#type' => 'textfield',
      '#title' => t('Folder name (optional)'),
      '#required' => FALSE,
      '#default_value' => "",
      '#description' => "Enter a folder name if you want your images to be kept in a separate subfolder.",
      '#size' => 20,
      '#maxlength' => 20,
    );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validate handler for fileup_upload_form().
 */
function fileup_upload_form_validate($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_extensions' => array('zip'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'temporary://')) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file'] = $file;
      
    }
    else {
      form_set_error('file', t('Failed to write the uploaded file to the site\'s file folder.'));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }
}

/**
 * Submit handler for fileup_upload_form().
 */
function fileup_upload_form_submit($form, &$form_state) {
  $file = $form_state['storage']['file'];
  
  $subfolder = $form_state['values']['foldername'];
  
  $archiver = archiver_get_archiver($file->uri);
    if (!$archiver) {
      throw new Exception(t('Cannot extract %file, not a valid archive.', array('%file' => $file->uri)));
    }
    $directory = variable_get('file_public_path', conf_path() . '/files/fileup_images' . (isset($subfolder) && $subfolder != '' ? "/$subfolder" : ""));
   
 $imgfiles = $archiver->listContents();
 
 $archiveok = true;
 
 for ($i = 0; $i < count($imgfiles); $i++) {
     $file_name = $imgfiles[$i];
     

    $regex = '/^.*\.(jpg|jpeg|png|gif|tiff|tif|bmp)$/i';
     if (!preg_match($regex, $file_name)) {
        $archiveok = false;
          form_set_error('file', t('The archive contains files that are not images. Nothing was uploaded.'));
         
         }
        
     }

 
if ($archiveok) { $imageinsert = $archiver->extract($directory,$imgfiles); 
    }

  // We are done with the zip file, remove it from storage.
  $imgnames = implode(', ', $imgfiles);
 $remove = file_delete($file);
 
  // Set a response to the user.

 if (isset($imageinsert)) { drupal_set_message(t('The archived images have been extracted and saved: ' .  $imgnames)); }
}
