using System;
using System.Collections.Generic;
using System.Text;

namespace Studio.Interface
{
    public class Engine
    {
        public Engine()
        {
            _binding = new EngineBindings();
            _engineObject = _binding.createEngineInstance();
        }

        ~Engine()
        {
            _binding.terminateEngineInstance(_engineObject);
        }

        public void initialize()
        {
            _binding.initializeEngineInstance(_engineObject);
        }

        public void execute()
        {
            _binding.executeEngineInstance(_engineObject);
        }

        private IntPtr _engineObject;
        private EngineBindings _binding;
    }
}
