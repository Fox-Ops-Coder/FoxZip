namespace FoxZip.Objects
{
    internal sealed class SizeAdapter
    {
        public uint Size { get; }

        public SizeAdapter(uint size)
        {
            Size = size;
        }

        public override string ToString()
        {
            return Size.ToString();
        }
    }
}