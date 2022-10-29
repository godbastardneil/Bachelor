using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.IO;
using System.Text.Json;

class Already_exist : ArgumentException
{
    public int Id { get; }
    public Already_exist(int _id)
    {
        Id = _id;
    }
}

namespace Lab2.Data
{
    public class Stud_Info_Repos
    {
        public string Fname;
        public Stud_Info_Repos(string name)
        {
            Fname = name;
        }

        /// <summary>
        /// Returns all items of the list
        /// </summary>
        /// <returns>List of data</returns>
        public List<Stud_Info> Read_List()
        {
            lock (this)
            {
                List<Stud_Info> SList = new List<Stud_Info>();
                StreamReader reader = new StreamReader(Fname);
                while (!reader.EndOfStream) // Deserialize
                {
                    string jtmp = reader.ReadLine();
                    try
                    {
                        SList.Add(JsonSerializer.Deserialize<Stud_Info>(jtmp));
                    }
                    catch { }
                }
                reader.Close();
                return SList;
            }
        }
        /// <summary>
        /// Serialize info about songs to file
        /// </summary>
        /// <param name="data">List of songs</param>
        public void Write_List(IList<Stud_Info> data)
        {
            lock (this)
            {
                StreamWriter SWriter = new StreamWriter(Fname); //Creating a stream to write to a file
                foreach (Stud_Info curSong in data) // Serialize
                    SWriter.WriteLine(JsonSerializer.Serialize(curSong));
                SWriter.Close();
            }
        }


        /// <summary>
        /// Add new data row
        /// </summary>
        /// <param name="data">New data row</param>
        public void Add(Stud_Info data)
        {
            lock (this)
            {
                // Deserialize data from file
                // Add new data
                // Save updated list to file

                IList<Stud_Info> L_students = Read_List();

                foreach (Stud_Info stud in L_students)
                {
                    if (stud.Id == data.Id) { throw new Already_exist(data.Id); }
                }

                L_students.Add(data);

                Write_List(L_students);
            }
        }

        /// <summary>
        /// Update data row
        /// </summary>
        /// <param name="data">Data row</param>
        public void Update(Stud_Info data)
        {
            lock (this)
            {
                // Deserialize data from file
                // Find data with same id
                // Update it's attributes
                // Save updated list to file

                IList<Stud_Info> L_students = Read_List();

                for (int i=0; i<L_students.Count; ++i)
                {
                    if (L_students[i].Id == data.Id)
                    {
                        L_students[i] = data;
                        Write_List(L_students);
                        return;
                    }
                }
            }
        }

        /// <summary>
        /// Remove data row
        /// </summary>
        /// <param name="id">Row id to remove</param>
        public void Remove(int id)
        {
            lock (this)
            {
                // Deserialize data from file
                // Find data with same id
                // Remove data row
                // Save updated list to file

                IList<Stud_Info> L_students = Read_List();

                for (int i = 0; i < L_students.Count; ++i)
                {
                    if (L_students[i].Id == id)
                    {
                        Console.WriteLine($"L_students-значения {i} - {id}, {L_students[i].FIO}");
                        L_students.RemoveAt(i);
                        foreach (Stud_Info st in L_students)
                        {
                            Console.WriteLine($"Table-значения - {st.Id}, {st.FIO}, {st.IsStar}");
                        }
                        Write_List(L_students);
                        return;
                    }
                }
            }
        }

        public Stud_Info Find(int id)
        {
            IList<Stud_Info> L_students = Read_List();

            for (int i = 0; i < L_students.Count; ++i)
            {
                if (L_students[i].Id == id)
                {
                    return L_students[i];
                }
            }
            return new Stud_Info();
        }
    }
}
