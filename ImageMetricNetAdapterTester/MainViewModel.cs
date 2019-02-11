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
        CoreLib _coreLib;

        public MainViewModel()
        {
            Path = @"d:\Борисов\jpeg degradation Double JPEG Compression\Image-Forgery-Detection\images\1837419_orig.jpg";

            _coreLib = new CoreLib();
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


        private int _jpegPeak;
        public int JpegPeak
        {
            get { return _jpegPeak; }
            set
            {
                _jpegPeak = value;
                RaisePropertyChangedEvent("JpegPeak");
            }
        }

        ICommand _goCommand;
        public ICommand GoCommand
        {
            get
            {
                return _goCommand ?? (_goCommand = new RelayCommand(arg =>
                
                {
                    JpegPeak = 0;
                    //CoreDll.WorkProgressInteropNegotiator negotiator = new CoreDll.WorkProgressInteropNegotiator();
                    //negotiator.reportProgress = new CoreDll.ReportProgressCallback(progressDialogViewModel.ReportProgress);
                    //negotiator.addToLogCallback = new CoreDll.AddToLogCallback(progressDialogViewModel.ReportLog);
                    //negotiator.cancellationPending = new CoreDll.CancellationPendingCallback(() => { return progressDialogViewModel.IsCancel; });

                    var metric = _coreLib.CalculateImageMetric(Path, null);
                    JpegPeak = metric.JpegPeak;
                }, arg => !String.IsNullOrEmpty(Path)));
            }
        }
    }
}
