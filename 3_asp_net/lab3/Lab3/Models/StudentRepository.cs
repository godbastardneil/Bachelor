using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using Microsoft.EntityFrameworkCore;

namespace Lab3.Models
{
    public class StudentRepository
    {
        private GroupContext GC;
        public StudentRepository(GroupContext gc) {
            GC = gc;
        }
        public async Task<IList<StudentModel>> List(int gr_Id)
        {
            return await GC.student
                .Where(x => x.idgroup == gr_Id)
                .OrderBy(x => x.idstudent)
                .ToListAsync();
        }
        public async Task Add(StudentModel data)
        {
            await GC.student.AddAsync(data);
            await GC.SaveChangesAsync();
        }
        
        public async Task Update(StudentModel data)
        {
            StudentModel up_stud = await GC.student.SingleAsync(x => x.idstudent == data.idstudent);
            
            up_stud.FIO = data.FIO;
            up_stud.headman_sign = data.headman_sign;
            up_stud.idgroup = data.idgroup;
            await GC.SaveChangesAsync();
        }
        
        public async Task Remove(int stud_id)
        {
            StudentModel del_stud = await GC.student.SingleAsync(x => x.idstudent == stud_id);
            
            GC.student.Remove(del_stud);
            await GC.SaveChangesAsync();
        }
        
        public async Task<StudentModel> GetById(int Id)
        {
            return await GC.student
                .SingleAsync(x => x.idstudent == Id);
        }
    }
}
