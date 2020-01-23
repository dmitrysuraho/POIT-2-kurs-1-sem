using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Compression;

namespace LabRab13
{
    public static class SDALog
    {
        static StreamWriter file = new StreamWriter(@"D:\sdalogfile.txt");
        public static StreamWriter OpenFile()
        {
            return file;
        }
        public static void CloseFile()
        {
            file.Close();
        }

    }
    static class SDADiskInfo
    {
        public static void FreeBytes()
        {
            foreach (var x in DriveInfo.GetDrives())
            {
                Console.WriteLine($"{x.Name} Available: {x.AvailableFreeSpace}");
            }
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nScan free drive space\n@");
            Console.WriteLine();
        }
        public static void FileSystem()
        {
            foreach (var x in DriveInfo.GetDrives())
            {
                Console.WriteLine($"{x.Name} Format: {x.DriveFormat}");
            }
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nScan file system\n@");
            Console.WriteLine();
        }
        public static void AllInfo()
        {
            foreach (var x in DriveInfo.GetDrives())
            {
                Console.WriteLine($"Name: {x.Name}, TotalSpace: {x.TotalSize}, Available: {x.AvailableFreeSpace}, Volume Label: {x.VolumeLabel}");
            }
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nScan total, available space and volume label of drive\n@");
            Console.WriteLine();
        }
    }

    static class SDAFileInfo
    {
        public static void Path(FileInfo file)
        {
            Console.WriteLine($"Path: {file.DirectoryName}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking path to file\nFile name: {file.Name}\nPath: {file.FullName}\n@");
            Console.WriteLine();
        }
        public static void AllInfo(FileInfo file)
        {
            Console.WriteLine($"Size: {file.Length}");
            Console.WriteLine($"Extension: {file.Extension}");
            Console.WriteLine($"Name: {file.Name}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking file size, extension and name\nFile name: {file.FullName}\nPath: {file.DirectoryName}\n@");
            Console.WriteLine();
        }
        public static void Time(FileInfo file)
        {
            Console.WriteLine($"Creation time: {file.CreationTime}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking file creation time\nFile name: {file.FullName}\nPath: {file.DirectoryName}\n@");
            Console.WriteLine();
        }
    }
    static class SDADirInfo
    {
        public static void Files(DirectoryInfo dir)
        {
            int num = 0;
            foreach (var x in dir.GetFiles())
            {
                num++;
            }
            Console.WriteLine($"Number of files: {num}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking number if files in directory\nPath: {dir.FullName}\n@");
            Console.WriteLine();
        }
        public static void Time(DirectoryInfo dir)
        {
            Console.WriteLine($"Creation time: {dir.CreationTime}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking directory creation time\nPath: {dir.FullName}\n@");
            Console.WriteLine();
        }
        public static void SubDir(DirectoryInfo dir)
        {
            int num = 0;
            foreach (var x in dir.GetDirectories())
            {
                num++;
            }
            Console.WriteLine($"Number of subdirectories: {num}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking number of subdirectories\nPath: {dir.FullName}\n@");
            Console.WriteLine();
        }
        public static void ParentDir(DirectoryInfo dir)
        {
            Console.WriteLine($"Parent directory: {dir.Parent}");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nChecking parent directory\nPath: {dir.FullName}\n@");
            Console.WriteLine();
        }
    }
    static class SDAFileManager
    {
        public static void WriteInFile()
        {
            string[] NumOfFiles = new string[50];
            string[] NumOfDir = new string[50];
            DirectoryInfo dir = new DirectoryInfo(@"C:\");
            Directory.CreateDirectory(@"D:\SDAInspect");
            StreamWriter file = new StreamWriter(@"D:\SDAInspect\sdadirinfo.txt");
            file.WriteLine("-----------Files-----------:");
            foreach (var x in dir.GetFiles())
            {
                file.WriteLine($"{x}");
            }
            file.WriteLine("\n-----------Directories-----------");
            foreach (var y in dir.GetDirectories())
            {
                file.WriteLine($"{y}");
            }
            file.Close();
            Console.WriteLine("File sdadirinfo.txt is created");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nCreating sdadirinfo.txt\nPath: {dir.FullName}\n@");
        }
        public static void CopyAndRenameFile()
        {
            File.Copy(@"D:\SDAInspect\sdadirinfo.txt", @"D:\SDAInspect\sdadirinfoNEW.txt");
            Console.WriteLine("File sdadirinfo.txt is copied and renamed");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nCopying and renaming sdadirinfo.txt\nPath: D:\\SDAInspect\\sdadirinfo.txt\n@");
        }
        public static void DeleteOldFile()
        {
            File.Delete(@"D:\SDAInspect\sdadirinfo.txt");
            Console.WriteLine("File sdadirinfo.txt is deleted");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nDeleting old sdadirinfo.txt\nPath: D:\\SDAInspect\\sdadirinfo.txt\n@");
            Console.WriteLine();
        }
        public static void NewDir()
        {
            Directory.CreateDirectory(@"D:\SDAFiles");
            DirectoryInfo dir = new DirectoryInfo(@"C:\Program Files\ASCON\KOMPAS-3D V16\Bin");
            foreach (var x in dir.GetFiles())
            {
                if (Equals(x.Extension, ".tlb"))
                {
                    File.Copy(@"C:\Program Files\ASCON\KOMPAS-3D V16\Bin\" + x.Name, @"D:\SDAFiles\" + x.Name);
                }
            }
            Console.WriteLine("New directory SDAFiles is created");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nCreating directory SDAFiles\nPath: {dir.FullName}\n@");
        }
        public static void MoveNewDir()
        {
            Directory.Move(@"D:\SDAFiles", @"D:\SDAInspect\SDAFiles");
            Console.WriteLine("New directory SDAFiles is moves");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nMoving directory SDAFiles\nPath: D:\\SDAFiles\n@");
        }
        public static void Zip()
        {
            ZipFile.CreateFromDirectory(@"D:\SDAInspect\SDAFiles", @"D:\Archive.rar");
            Console.WriteLine("Zip Archive.rar is created");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nCreating Zip Archive.rar\nPath: D:\\SDAInspect\\SDAFiles\n@");
        }
        public static void Unzip()
        {
            ZipFile.ExtractToDirectory(@"D:\Archive.rar", @"D:\SDAInspect");
            Console.WriteLine("Unzipping is successful");
            SDALog.OpenFile().WriteLine($"{DateTime.Now}\nUnzipping Archive.rar\nPath:  D:\\SDAInspect\n@");
        }
    }

    static class FindInfo
    {
        public static void Find()
        {
            string[] str = new string[69];
            int num = 0;
            StreamReader file = new StreamReader(@"D:\sdalogfile.txt");
            for (int i = 0; i < 69; i++)
            {
                if (Equals(file.ReadLine(), "@"))
                {
                    num++;
                }
            }
            //for (int i = 1; i < 69; i++)
            //{
            //    file.ReadLine();
            //    if (file.ReadLine().Contains("Path"))
            //    {
            //        while (!Equals(file.ReadLine(), "@"))
            //        {
            //            i--;
            //        }
            //        while (Equals(file.ReadLine(), "@"))
            //        {
            //            Console.WriteLine(file.ReadLine());
            //            i++;
            //        }

            //    }
            //}
            file.Close();
            Console.WriteLine(num);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.ReadKey();
            SDADiskInfo.FreeBytes();
            Console.ReadKey();
            SDADiskInfo.FileSystem();
            Console.ReadKey();
            SDADiskInfo.AllInfo();

            FileInfo file = new FileInfo(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\README.md");
            Console.ReadKey();
            SDAFileInfo.Path(file);
            Console.ReadKey();
            SDAFileInfo.AllInfo(file);
            Console.ReadKey();
            SDAFileInfo.Time(file);

            DirectoryInfo dir = new DirectoryInfo(@"C:\Users\Dmitry\Desktop\labrab\ООП");
            Console.ReadKey();
            SDADirInfo.Files(dir);
            Console.ReadKey();
            SDADirInfo.Time(dir);
            Console.ReadKey();
            SDADirInfo.SubDir(dir);
            Console.ReadKey();
            SDADirInfo.ParentDir(dir);

            Console.ReadKey();
            SDAFileManager.WriteInFile();
            Console.ReadKey();
            SDAFileManager.CopyAndRenameFile();
            Console.ReadKey();
            SDAFileManager.DeleteOldFile();
            Console.ReadKey();
            SDAFileManager.NewDir();
            Console.ReadKey();
            SDAFileManager.MoveNewDir();
            Console.ReadKey();
            SDAFileManager.Zip();
            Console.ReadKey();
            SDAFileManager.Unzip();
            Console.ReadKey();
            Console.WriteLine();

            //FindInfo.Find();

            SDALog.CloseFile();
        }
    }
}
