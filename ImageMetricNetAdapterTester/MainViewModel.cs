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
            Path = @"d:\Борисов\jpeg degradation Double JPEG Compression\Image-Forgery-Detection\images\1837419_orig_2_best.jpg";
            DirectoryPath = @"d:\Борисов\jpeg degradation Double JPEG Compression\Image-Forgery-Detection\images";

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


        private uint _jpegPeak;
        public uint JpegPeak
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

        private string _directoryPath;
        public string DirectoryPath
        {
            get { return _directoryPath; }
            set
            {
                _directoryPath = value;
                RaisePropertyChangedEvent("DirectoryPath");
            }
        }

        ICommand _multiImageCommand;
        public ICommand MultiImageCommand
        {
            get
            {
                return _multiImageCommand ?? (_multiImageCommand = new RelayCommand(arg =>
                {
                    CoreDll.WorkProgressInteropNegotiator negotiator = new CoreDll.WorkProgressInteropNegotiator();
                    //negotiator.reportProgress = new CoreDll.ReportProgressCallback(progressDialogViewModel.ReportProgress);
                    //negotiator.cancellationPending = new CoreDll.CancellationPendingCallback(() => { return progressDialogViewModel.IsCancel; });

                    var files = System.IO.Directory.GetFiles(DirectoryPath);
                    var infos = files.Select(f => new CoreDll.ImageInfo() { Path = f }).ToArray();

                    var startTime = System.Diagnostics.Stopwatch.StartNew();

                    _coreLib.CalculateMultiImageMetric(infos, negotiator);

                    startTime.Stop();
                    var resultTime = startTime.Elapsed;
                    // elapsedTime - строка, которая будет содержать значение затраченного времени
                    string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:000}",
                        resultTime.Hours,
                        resultTime.Minutes,
                        resultTime.Seconds,
                        resultTime.Milliseconds);

                    System.Windows.MessageBox.Show(String.Format("Посчитали histogram для {0} файлов! За {1}", infos.Length, elapsedTime));

                }, arg => !String.IsNullOrEmpty(Path)));
            }
        }
    }
}
