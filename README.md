
# react-native-superpowered-io-bridge

This library its a simple implementation of the Superpowered SDK in react-native **(only for Andriod for now)**. The only thing that this module does is to bridge the input to the output (be careful with the feedback). It uses the SuperpoweredStereoMixer for control panning. That control ocurrs at react native, enabling and disabling left or right channel. Use a headset for testing it.

If you want to add any effect, the magic succed at AudioIOBridge.cpp::audioProcessing

Refer to the [Superpowered SDK repository](https://github.com/superpoweredSDK/Low-Latency-Android-iOS-Linux-Windows-tvOS-macOS-Interactive-Audio-Platform/) for more examples and library docs

## Getting started

`$ npm install furiedev/react-native-superpowered-io-bridge --save`

### Mostly automatic installation

`$ react-native link react-native-superpowered-io-bridge`

### Manual installation

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.superpowerediobridge.RNSuperpoweredIoBridgePackage;` to the imports at the top of the file
  - Add `new RNSuperpoweredIoBridgePackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-superpowered-io-bridge'
  	project(':react-native-superpowered-io-bridge').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-superpowered-io-bridge/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-superpowered-io-bridge')
  	```

## Usage
```javascript

import React, { Component } from "react";
import {
  StyleSheet,
  Text,
  View,
  TouchableHighlight,
  NativeModules
} from "react-native";

type Props = {};
export default class App extends Component<Props> {
  constructor(props) {
    super(props);

    this.state = {
      playing: false,
      panning: {
        left: 1.0,
        right: 1.0
      },
      returned: ""
    };
  }

  componentDidMount() {
    NativeModules.RNSuperpoweredIoBridge.initialize()
      .then(() => {
        return NativeModules.RNSuperpoweredIoBridge.ToggleStartStop();
      })
      .then(playing => {
        this.setState({ playing });
      });
  }

  toggleLeft() {
    var { left, right } = this.state.panning;
    if (left === 1.0) {
      left = 0.0;
    } else {
      left = 1.0;
    }
    this.updatePanning(left, right);
    this.setState({
      panning: { left, right }
    });
  }

  toggleRight() {
    var { left, right } = this.state.panning;
    if (right === 1.0) {
      right = 0.0;
    } else {
      right = 1.0;
    }
    this.updatePanning(left, right);
    this.setState({
      panning: { left, right }
    });
  }

  updatePanning(left, right) {
    NativeModules.RNSuperpoweredIoBridge.updatePanning(left, right);
  }

  render() {
    return (
      <View style={styles.container}>
        <TouchableHighlight
          style={styles.button}
          onPress={() => {
            this.toggleLeft();
          }}
        >
          <Text style={{ color: "#fff" }}>Left</Text>
        </TouchableHighlight>
        <Text style={styles.label}>
          Left: {this.state.panning.left ? "ON" : "OFF"}
        </Text>
        <TouchableHighlight
          style={styles.button}
          onPress={() => {
            this.toggleRight();
          }}
        >
          <Text style={{ color: "#fff" }}>Right</Text>
        </TouchableHighlight>
        <Text style={styles.label}>
          Right: {this.state.panning.right ? "ON" : "OFF"}
        </Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#F5FCFF"
  },
  label: {
    fontSize: 20,
    textAlign: "center",
    margin: 10
  },
  button: {
    backgroundColor: "#22d",
    padding: 10
  }
});

```
  