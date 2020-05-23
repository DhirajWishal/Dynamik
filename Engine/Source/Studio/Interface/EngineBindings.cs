using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

namespace Studio.Interface
{
    public class EngineBindings
    {
        [DllImport("StudioInterface.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern IntPtr createInterface();

        [DllImport("StudioInterface.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern void initialize(IntPtr obj);

        [DllImport("StudioInterface.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern IntPtr execute(IntPtr obj);

        [DllImport("StudioInterface.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern IntPtr terminate(IntPtr obj);

        public IntPtr createEngineInstance()
        {
            return createInterface();
        }

        public void initializeEngineInstance(IntPtr _object)
        {
            initialize(_object);
        }

        public void executeEngineInstance(IntPtr _object)
        {
            execute(_object);
        }

        public void terminateEngineInstance(IntPtr _object)
        {
            terminate(_object);
        }
    }
}
