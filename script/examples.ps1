$outputFolder = "..\out\"
$720pFiles = "..\img-noised\0_720p.bmp|..\img-noised\1_720p.bmp|..\img-noised\2_720p.bmp|..\img-noised\3_720p.bmp"
$1080pFiles = "..\img-noised\0_1080p.bmp|..\img-noised\1_1080p.bmp|..\img-noised\2_1080p.bmp|..\img-noised\3_1080p.bmp"
$2160pFiles = "..\img-noised\0_2160p.bmp|..\img-noised\1_2160p.bmp|..\img-noised\2_2160p.bmp|..\img-noised\3_2160p.bmp"
$4320pFiles = "..\img-noised\0_4320p.bmp|..\img-noised\1_4320p.bmp|..\img-noised\2_4320p.bmp|..\img-noised\3_4320p.bmp"



Write-Output "`n`nSerial, bucketsort, 3x3 kernel, 720p"
& .\parallel.exe median-filter 3 bucket 1 $720pFiles $outputFolder
Write-Output  "`n`nSerial, bucketsort, 3x3 kernel, 1080p"
& .\parallel.exe median-filter 3 bucket 1 $1080pFiles $outputFolder
Write-Output  "`n`nSerial, bucketsort, 3x3 kernel, 2160p"
& .\parallel.exe median-filter 3 bucket 1 $2160pFiles $outputFolder
Write-Output  "`n`nSerial, bucketsort, 3x3 kernel, 4320p"
& .\parallel.exe median-filter 3 bucket 1 $4320pFiles $outputFolder



Write-Output "`nSerial execution, bucketsort, variable kernelsize`n`n"
Write-Output "sort`tkernel_size`ttime"

for ($kernelSize = 51; $kernelSize -le 201; $kernelSize += 2)
{
    $avgLine = & ..\x64\Release\parallel.exe median-filter $kernelSize bucket 1 $1080pFiles $outputFolder | findstr /i "avg"
	$avgTime = $avgLine.Split("`t")[1]
	Write-Output "bucket $kernelSize`t$avgTime"
	
	$avgLine = & ..\x64\Release\parallel.exe median-filter $kernelSize quick 1 $1080pFiles $outputFolder | findstr /i "avg"
	$avgTime = $avgLine.Split("`t")[1]
	Write-Output "quick $kernelSize`t$avgTime"
}



$resolutions = "720p", "1080p", "2160p", "4320p"
$kernelSizes = 5, 11, 25, 49

Write-Output "`nParallel traversal, variable kernelsize, serial quicksort`n`n"
Write-Output "resolution`tkernel_size`ttime"

foreach ($resolution in $resolutions)
{
	foreach ($kernelSize  in $kernelSizes)
	{
		$fileList = "..\img-noised\0_$resolution.bmp|..\img-noised\1_$resolution.bmp|..\img-noised\2_$resolution.bmp|..\img-noised\3_$resolution.bmp";
		$avgLine = & .\parallel.exe median-filter $kernelSize quick 0 $fileList $outputFolder | findstr /i "avg"
		$avgTime = $avgLine.Split("`t")[1]
		Write-Output "$resolution`t$kernelSize`t$avgTime"
	}
}


$threadCounts = 1, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100
$kernelSizes = 5, 11, 25, 49

Write-Output "`nVariable threads, variable kernelsize, variable sort`n`n"
Write-Output "threads`tkernel_size`ttime"

foreach ($threads in $threadCounts)
{
	foreach ($kernelSize  in $kernelSizes)
	{
		$sortingFunction = If ($kernelSize -gt 35) {"bucket"} Else {"quick"}
		$avgLine = & ..\x64\Release\parallel.exe median-filter $kernelSize $sortingFunction $threads $1080pFiles $outputFolder | findstr /i "avg"
		$avgTime = $avgLine.Split("`t")[1]
		Write-Output "$threads`t$kernelSize`t$avgTime"
	}
}