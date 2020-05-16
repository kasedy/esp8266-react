import React, { Component } from 'react';
import { ValidatorForm } from 'react-material-ui-form-validator';

import { Paper, Typography, Box, Switch, Slider, Select, MenuItem, InputLabel, NativeSelect, TextField, FormControl } from '@material-ui/core';
import { WEB_SOCKET_ROOT } from '../api';
import { SocketControllerProps, SocketFormLoader, SocketFormProps, socketController } from '../components';
import { SectionContent, BlockFormControlLabel } from '../components';
import { createStyles, Theme, makeStyles, WithStyles, withStyles } from '@material-ui/core/styles';

import { LightSettings } from './types';

export const LIGHT_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "light_status";

const styles = (theme: Theme) => createStyles({
  content: {
    display: "flex",
    justifyContent: "center",
    flexDirection: "column",
    textAlign: "center",
    padding: theme.spacing(2),
    margin: theme.spacing(3),
    marginLeft: 'auto',
    marginRight: 'auto',
    maxWidth: theme.breakpoints.values.sm,
  },

});

const useStyles = makeStyles((theme: Theme) =>
  createStyles({
    inputOnTheLeft: {
      textAlign: 'left'
    },
    labelWrapper: {
      width: '100%',
      paddingTop: theme.spacing(4),
    }
  })
);

type LightSettingsSocketControllerProps = SocketControllerProps<LightSettings>;

class LightSettingsSocketController extends Component<LightSettingsSocketControllerProps & WithStyles<typeof styles>> {

  render() {
    return (
      <Paper className={this.props.classes.content}>
        <Typography variant="h4" gutterBottom>
          Countreau Bottle
        </Typography>
        <SocketFormLoader
          {...this.props}
          render={props => (
            <LightSettingsSocketControllerForm {...props} />
          )}
        />
      </Paper>
    )
  }
}

export default socketController(LIGHT_SETTINGS_WEBSOCKET_URL, 100, withStyles(styles)(LightSettingsSocketController));

type LightSettingsSocketControllerFormProps = SocketFormProps<LightSettings>;

function LightSettingsSocketControllerForm(props: LightSettingsSocketControllerFormProps) {
  const { data, saveData, setData } = props;

  const handleValueChange = (name: string) => {
    return (event: any, value: any) => {
      setData({ ...data, [name]: value }, saveData);
    };
  }

  const renderEffectListItems = () => {
    return data.effect_list.map((name: any, index: any) => (
      <MenuItem key={index} value={index}>{name}</MenuItem>
    ));
  }

  const classes = useStyles();

  const setEffect = (event: any) => {
    setData({ ...data, 'effect': parseInt(event.target.value) }, saveData);
  }

  return (
    <Box display="flex" alignItems="center" flexDirection="column">
        <BlockFormControlLabel
          control={
            <Switch
              checked={data.state}
              onChange={handleValueChange('state')}
              color="primary"
            />
          }
          label="Enable"
          labelPlacement='start'
          className={classes.labelWrapper}
        />
        <Box className={classes.labelWrapper}>
          <InputLabel className={classes.inputOnTheLeft}>Brightness</InputLabel>
        </Box>
        <Slider 
          value={data.brightness}
          min={0}
          max={255}
          onChange={handleValueChange('brightness')}
          valueLabelFormat={(value) => `${Math.trunc((value + 0.5) / 256 * 100 + 0.5)}%` }
          valueLabelDisplay='auto' />
        <Box className={classes.labelWrapper}>
          <InputLabel className={classes.inputOnTheLeft}>Effect speed</InputLabel>
        </Box>
        <Slider 
          value={data.speed}
          min={0}
          max={255}
          onChange={handleValueChange('speed')}
          valueLabelFormat={(value) => `${Math.trunc((value + 0.5) / 256 * 100 + 0.5)}%` }
          valueLabelDisplay='auto' />
        <Box className={classes.labelWrapper}>
          <InputLabel className={classes.inputOnTheLeft}>Effect</InputLabel>
        </Box>
        <FormControl variant="outlined" margin="normal" fullWidth>
          <Select
            native
            value={data.effect}
            onChange={setEffect}
          >
            {data.effect_list.map((name: any, index: any) => (
              <option key={index} value={index}>{name}</option>
            ))}
          </Select>
        </FormControl>      
    </Box>
  );
}
