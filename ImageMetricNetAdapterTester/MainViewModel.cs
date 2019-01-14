using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ImageMetricNetAdapter;

namespace ImageMetricNetAdapterTester
{
    class MainViewModel : PropertyChangedBase
    {
        public MainViewModel()
        {
            Path = @"d:\Борисов\SoftMy\ImageComparer1.png";
        }

        private string _path;
        public string Path
        {
            get { return _path; }
            set
            {
                _path = value;
                RaisePropertyChangedEvent("Path");
            }
        }

        ICommand _goCommand;
        public ICommand GoCommand
        {
            get
            {
                return _goCommand ?? (_goCommand = new RelayCommand(arg =>
                {
                    var core = new CoreLib();
                }, arg => !String.IsNullOrEmpty(Path)));
            }
        }
    }
}
