using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication4
{
    class PrintCollectoin
    {
        List<string> collection_s = new List<string>();
        public static void MakeMixList<t>(IList<t> list)
        {
            Random r = new Random();

            SortedList<int, t> mixedList = new SortedList<int, t>();
            foreach (t item in list)
                mixedList.Add(r.Next(), item);

            list.Clear();
            for (int i = 0; i < mixedList.Count; i++)
            {
                list.Add(mixedList.Values[i]);
            }
        }
        public void SetFileNames (List<string> list)
        {
            collection_s = list;
            MakeMixList(collection_s);
        }
        public string GetFileName()
        {
            if (collection_s.Count==0 )return "";
            string s = collection_s[0];
            collection_s.RemoveRange(0, 1);
            return s;
        }
        public int GetCount()
        {
            return collection_s.Count;
        }
    }
}
