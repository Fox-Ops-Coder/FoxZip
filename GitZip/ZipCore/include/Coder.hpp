#ifndef CODER_HPP
#define CODER_HPP

namespace FoxCoder
{
	public ref class Coder
	{
		public:
			Coder();
			~Coder();

			const bool CompressFile(System::String^ sourceFilePath, System::String^ archiveFilePath, unsigned long tableSize);
			const bool DecompressFile(System::String^ archiveFilePath, System::String^ outPutDir);

			int GetStep();
			void Stop();
			bool Interupted();

		private:
			int* const step;
			bool* const stop;

			bool ended;
	};
}

#endif // !CODER_HPP