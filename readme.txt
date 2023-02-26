Angel URIOT
Arthur AZAMBRE
Guillaume DESCOMPS

Final assignment

Notes:

New features:

	- Bump mapping

	- Specular mapping

	- Multithreading
		- with soft-shadows.yaml for example:
			- 1 thread: 2min 19s
			- 32 threads: 10s (yes I have a 32 threads CPU)

	- Mesh optimization with a bounding box
		- with dolphin.yaml for example:
			- without: 17s
			- with: 11s

Run build_vs.bat to build a Visual Studio solution
