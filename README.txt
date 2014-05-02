What is Segaudio?

	Segaudio is a C++ application for content-based file-to-file audio search.

What is content-based audio search?

	Rather than using something like text tags attached to audio file, Segaudio uses the actual audio information such as frequencies or loudness to search.

What can it be used for?

	Generally, to search for particular pieces of audio in a file and export them in a separate audio file(s).  It’s most useful for speeding up the process of manual ear inspection to search for audio. Examples include finding the songs in a recording of the church service or finding all the thunderclaps in a recording of a rainstorm.

How much does it cost?

	Segaudio is open-source and free. The source is available on my Github account at https://github.com/scaubrey/Segaudio.

Is there a tutorial?

	Yes, check out the screencasts at www.CameronSummers.com.


Segaudio Features:

•	File-to-file audio search
•	Select any single part of a reference file
•	Four disparate statistical features (Mel Frequency Cepstral Coefficients, Spectral Centroid, Root Mean Square, Zero Cross Rate) to cover a wide range of uses
•	Use any combination of features or all of them
•	Full audio transport allows positional playback to audition candidate regions for extraction
•	Zoom capability for finer visual inspection
•	Rapid file changing for both reference and target
•	Application state awareness to provide UI feedback for better usability
•	Fine resolution controllers for clustering parameters (threshold, smoothing, and region width filtering)
•	Region inversion allows extraction of similar or dissimilar regions
•	Mouse drag to edit region boundaries
•	Manual mode for adding and removing regions - seamless integration with automated mode
•	Primitive searching capability to find a given number of regions in a target file
•	Audio export supports combining the regions into a single file or creating individual files for each
•	Region boundary export saves a CSV file with region boundaries in seconds


Keywords: audio, search, segmentation, computer, application,  program, C++
