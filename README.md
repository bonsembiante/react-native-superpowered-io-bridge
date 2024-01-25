
# react-native-superpowered-io-bridge

## Getting started

`$ npm install react-native-superpowered-io-bridge --save`

### Mostly automatic installation

`$ react-native link react-native-superpowered-io-bridge`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-superpowered-io-bridge` and add `RNSuperpoweredIoBridge.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNSuperpoweredIoBridge.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.RNSuperpoweredIoBridgePackage;` to the imports at the top of the file
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

#### Windows
[Read it! :D](https://github.com/ReactWindows/react-native)

1. In Visual Studio add the `RNSuperpoweredIoBridge.sln` in `node_modules/react-native-superpowered-io-bridge/windows/RNSuperpoweredIoBridge.sln` folder to their solution, reference from their app.
2. Open up your `MainPage.cs` app
  - Add `using Superpowered.Io.Bridge.RNSuperpoweredIoBridge;` to the usings at the top of the file
  - Add `new RNSuperpoweredIoBridgePackage()` to the `List<IReactPackage>` returned by the `Packages` method


## Usage
```javascript
import RNSuperpoweredIoBridge from 'react-native-superpowered-io-bridge';

// TODO: What to do with the module?
RNSuperpoweredIoBridge;
```
  