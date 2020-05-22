using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Runtime.InteropServices;
using Studio.Interface;

namespace Studio
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            EngineBindings _binding = new EngineBindings();

            IntPtr _object = _binding.createEngineInstance();
            _binding.initializeEngineInstance(_object);
            _binding.exexuteEngineInstance(_object);

            InitializeComponent();
        }
    }
}
