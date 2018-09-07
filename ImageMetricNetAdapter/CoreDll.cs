using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;


namespace ImageMetricNetAdapter
{
    public enum Compare : int
    {
        HEngineComparator = 0,
        LinearComparator = 1,
        HEngineFileComparator = 2,
    }

    public enum InfoFromHashMode : int
    {
        Map = 0,
        KyotoHashDB = 1,
    }

    public class CoreDll : DynamicModule
    {
        public CoreDll()
            : base(IntPtr.Size == 8 ? "ImageComparer64.dll" : "ImageComparer32.dll")
        {
        }

        #region API constants

        public const int FALSE = 0;
        public const int TRUE = 1;

        public const int MAX_PATH_LENGTH_FOR_SEARCH_DIRECTORY = 256;
        public const int MAX_PATH_LENGTH = 32767;

        #endregion

        #region API enumerations

        public enum Error : int
        {
            Ok = 0,
            Unknown = 1,
            InvalidPointer = 2
        }

        #endregion

        #region API functions

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error Initializes_fn();
        [DynamicModuleApi]
        public Initializes_fn Initialize = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error BeforeRelease_fn();
        [DynamicModuleApi]
        public BeforeRelease_fn BeforeRelease = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error ComputeHashes_fn([In, Out] WorkProgressInteropNegotiator negotiator);
        [DynamicModuleApi]
        public ComputeHashes_fn ComputeHashes = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error CompareHashes_fn([In, Out] WorkProgressInteropNegotiator negotiator);
        [DynamicModuleApi]
        public CompareHashes_fn CompareHashes = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error PostCheckBySURF_fn([In, Out] WorkProgressInteropNegotiator negotiator);
        [DynamicModuleApi]
        public PostCheckBySURF_fn PostCheckBySURF = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error OptionsSet_fn([In, Out] DllModel options);
        [DynamicModuleApi]
        public OptionsSet_fn OptionsSet = null;

        /*[UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate IntPtr GetFinalResult_fn([Out]out uint size);
        [DynamicModuleApi]
        public GetFinalResult_fn GetFinalResult = null;*/

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate uint GetResultSize_fn();
        [DynamicModuleApi]
        public GetResultSize_fn GetResultSize = null;

        /*[UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate IntPtr GetResult_fn(uint index);
        [DynamicModuleApi]
        public GetResult_fn GetResult = null;*/

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error FillResult_fn(IntPtr exportResult, uint index);
        //public delegate Error FillResult_fn([In, Out] DuplPairExport exportResult, [In] uint index);
        [DynamicModuleApi]
        public FillResult_fn FillResult = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error DrawMathes_fn(string firstImage, string secondImage);
        [DynamicModuleApi]
        public DrawMathes_fn DrawMathes = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error ClearHashStrorage_fn([In, Out] WorkProgressInteropNegotiator negotiator, bool deleteResized);
        [DynamicModuleApi]
        public ClearHashStrorage_fn ClearHashStrorage = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate Error ClearSearchPath_fn();
        [DynamicModuleApi]
        public ClearSearchPath_fn ClearSearchPath = null;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate Error AddSearchPath_fn([In] SearchPath searchPath);
        [DynamicModuleApi]
        public AddSearchPath_fn AddSearchPath = null;

        #endregion

        #region API structure

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public delegate void ReportProgressCallback(uint currentStep, uint maxStep, string message);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public delegate void AddToLogCallback(string message);

        public delegate bool CancellationPendingCallback();

        [StructLayout(LayoutKind.Sequential)]
        public class WorkProgressInteropNegotiator
        {
            public ReportProgressCallback reportProgress;

            public AddToLogCallback addToLogCallback;

            public CancellationPendingCallback cancellationPending;

#pragma warning disable 0649
            // C# does not see this member is set up in native code, we disable warning to avoid it.
            public bool cancel;
#pragma warning restore 0649
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Result
        {
            public uint DelThumsCount;
            public uint DelZeroCount;
            public uint UnknowedCount;
            public uint RenameCount;
            public uint ErrorExtensionCount;
        }



        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct ImageInfo
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PATH_LENGTH)]
            public string Path;
            public double JpegQuality;
            public double Sharpness;
            public uint FileSize;
            public uint Width;
            public uint Height;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct DuplPairExport
        {
            public ImageInfo FirstFile;
            public ImageInfo SecondFile;
            public uint CountOfHashes;
            //public uint TotalHashes;
        }


        #endregion


    }
}
