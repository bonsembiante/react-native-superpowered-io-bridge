using ReactNative.Bridge;
using System;
using System.Collections.Generic;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

namespace Superpowered.Io.Bridge.RNSuperpoweredIoBridge
{
    /// <summary>
    /// A module that allows JS to share data.
    /// </summary>
    class RNSuperpoweredIoBridgeModule : NativeModuleBase
    {
        /// <summary>
        /// Instantiates the <see cref="RNSuperpoweredIoBridgeModule"/>.
        /// </summary>
        internal RNSuperpoweredIoBridgeModule()
        {

        }

        /// <summary>
        /// The name of the native module.
        /// </summary>
        public override string Name
        {
            get
            {
                return "RNSuperpoweredIoBridge";
            }
        }
    }
}
