import React from 'react';
import { TextValidator, ValidatorForm } from 'react-material-ui-form-validator';

import SaveIcon from '@material-ui/icons/Save';

import { RestFormProps, FormActions, FormButton } from '../components';

import { HomeAssistantSettings } from './types';

type HomeAssistantSettingsFormProps = RestFormProps<HomeAssistantSettings>;

class HomeAssistantSettingsForm extends React.Component<HomeAssistantSettingsFormProps> {
  render() {
    const { data, handleValueChange, saveData, loadData } = this.props;
    return (
      <ValidatorForm onSubmit={saveData}>
        <TextValidator
          // validators={['required']}
          // errorMessages={['Home Assistant device display is required']}
          name="name"
          label="Device disaply name"
          fullWidth
          variant="outlined"
          value={data.name}
          onChange={handleValueChange('name')}
          margin="normal"
        />
        <FormActions>
          <FormButton startIcon={<SaveIcon />} variant="contained" color="primary" type="submit">
            Save
          </FormButton>
          <FormButton variant="contained" color="secondary" onClick={loadData}>
            Reset
          </FormButton>
        </FormActions>
      </ValidatorForm>
    );
  }
}

export default HomeAssistantSettingsForm;
