using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;


namespace ImageMetricNetAdapter
{
    public class CoreLib : IDisposable
    {
        private CoreDll _dll = null;

        //-----------Public functions----------------------------------------------

        public CoreLib()
        {
            try
            {
                _dll = new CoreDll();
            }
            catch (Exception ex)
            {
                throw new Exception("Can't load core library! " + Environment.NewLine + ex.Message);
            }
            _dll.Initialize();
            //_handle = _dll.adCreate();

            /*if (Version.Compatible(GetVersion(CoreDll.VersionType.AntiDupl)))
            {
                _handle = _dll.adCreate();
            }
            else
                throw new Exception("Incompatible core library version!");*/
        }

        ~CoreLib()
        {
            Dispose();
        }

        public void Dispose()
        {
            //Release();
            if (_dll != null)
            {
                _dll.BeforeRelease();
                _dll.Dispose();
                _dll = null;
            }
            GC.SuppressFinalize(this);
        }

        public void Release()
        {
            //_dll.BeforeRelease();
            /*if (_dll != null)
            {
                if (_dll.Release() == CoreDll.Error.AccessDenied)
                {
                    Stop();
                    Thread.Sleep(10);
                    m_dll.adRelease(m_handle);
                }
            }*/
        }


        public CoreDll.Error ComputeHashes(CoreDll.WorkProgressInteropNegotiator negotiator)
        {
            return _dll.ComputeHashes(negotiator);
        }

        public CoreDll.Error CompareHashes(CoreDll.WorkProgressInteropNegotiator negotiator)
        {
            return _dll.CompareHashes(negotiator);
        }

        public CoreDll.Error PostCheckBySURF(CoreDll.WorkProgressInteropNegotiator negotiator)
        {
            return _dll.PostCheckBySURF(negotiator);
        }


        /*public ViewResultOfDupl[] GetResult()
        {
            uint size;
            IntPtr ptr = _dll.GetFinalResult(out size);
            // Create the managed array that will be returned
            CoreDll.DuplPairExport[] array = new CoreDll.DuplPairExport[size];
            // For efficiency, only compute the element size once
            int elemSize = Marshal.SizeOf(typeof(CoreDll.DuplPairExport));
            // Populate the array
            for (int i = 0; i < size; i++)
            {
                array[i] = (CoreDll.DuplPairExport)Marshal.PtrToStructure(ptr + (elemSize * i), typeof(CoreDll.DuplPairExport));
            }
            //return array.Select(a => a.Path).ToArray();
            return array.Select(a => new ViewResultOfDupl(a)).ToArray();
        }*/

        /*
        public DuplPairViewModel[] GetResult2()
        {
            List<DuplPairViewModel> result = new List<DuplPairViewModel>();
            uint size;
            size = _dll.GetResultSize();
            // For efficiency, only compute the element size once
            int elemSize = Marshal.SizeOf(typeof(CoreDll.DuplPairExport));
            // Populate the array
            for (uint i = 0; i < size; i++)
            {
                // Initialize unmanged memory to hold the struct.
                IntPtr ptr = Marshal.AllocHGlobal(elemSize);

                //CoreDll.DuplPairExport str = new CoreDll.DuplPairExport();

                // Copy the struct to unmanaged memory.
                // Marshal.StructureToPtr(str, ptr, false);

                //IntPtr ptr = _dll.GetResult(i);
                //CoreDll.DuplPairExport dpExport = _dll.GetResult(i);
                _dll.FillResult(ptr, i);

                CoreDll.DuplPairExport dpExport = (CoreDll.DuplPairExport)Marshal.PtrToStructure(ptr, typeof(CoreDll.DuplPairExport));
                CheckDPExport(dpExport);
                result.Add(new DuplPairViewModel(dpExport));

                // Clean-up
                Marshal.DestroyStructure(ptr, typeof(CoreDll.DuplPairExport));
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(ptr);
            }
            return result.ToArray();
        }

        private void CheckDPExport(CoreDll.DuplPairExport dpExport)
        {
            if (dpExport.FirstFile.JpegQuality < 0)
                throw new ArgumentException("FirstFile.JpegQuality < 0");
            if (dpExport.SecondFile.JpegQuality < 0)
                throw new ArgumentException("SecondFile.JpegQuality < 0");
            if (dpExport.FirstFile.Sharpness < 0)
                throw new ArgumentException("FirstFile.Sharpness < 0");
            if (dpExport.SecondFile.Sharpness < 0)
                throw new ArgumentException("SecondFile.Sharpness < 0");

            if (dpExport.FirstFile.FileSize == 0)
                throw new ArgumentException(String.Format("FileSize for {0} is 0!", dpExport.FirstFile.Path));
            if (dpExport.SecondFile.FileSize == 0)
                throw new ArgumentException(String.Format("FileSize for {0} is 0!", dpExport.SecondFile.Path));
        }

        public void SetOptions(DllModel model)
        {
            _dll.OptionsSet(model);
        }

        public bool DrawMathes(string firstImage, string secondImage)
        {
            return _dll.DrawMathes(firstImage, secondImage) == CoreDll.Error.Ok;
        }

        public bool ClearHashStrorage(CoreDll.WorkProgressInteropNegotiator negotiator, bool deleteResized)
        {
            if (_dll.ClearHashStrorage == null)
                throw new NullReferenceException("Функции ClearHashStrorage в библиотеке не существует!");
            return _dll.ClearHashStrorage(negotiator, deleteResized) == CoreDll.Error.Ok;
        }

        public bool SetSearchPath(IEnumerable<SearchPath> searchPathList)
        {
            _dll.ClearSearchPath();
            foreach (SearchPath item in searchPathList)
            {
                _dll.AddSearchPath(item);
            }
            return true;
        }*/
    }
}
