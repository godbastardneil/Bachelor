using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Lab4.Server.Data;
using Lab4.Shared.Domain;
using Microsoft.EntityFrameworkCore;

namespace Lab4.Server.Repositories
{
    public class StudentRepository
    {
        private ApplicationDbContext AC;
        public StudentRepository(ApplicationDbContext gc) {
            AC = gc;
        }
        public async Task<IList<StudentModel>> List(Guid gr_Id)
        {
            return await AC.students
                .Where(x => x.idgroup == gr_Id)
                .OrderBy(x => x.idstudent)
                .ToListAsync();
        }
        public async Task Add(StudentModel data)
        {
            await AC.students.AddAsync(data);
            await AC.SaveChangesAsync();
        }
        
        public async Task Update(StudentModel data)
        {
            StudentModel up_stud = await AC.students.SingleAsync(x => x.idstudent == data.idstudent);
            
            up_stud.FIO = data.FIO;
            up_stud.headman_sign = data.headman_sign;
            up_stud.idgroup = data.idgroup;
            await AC.SaveChangesAsync();
        }
        
        public async Task Remove(Guid stud_id)
        {
            StudentModel del_stud = await AC.students.SingleAsync(x => x.idstudent == stud_id);
            
            AC.students.Remove(del_stud);
            await AC.SaveChangesAsync();
        }
        
        public async Task<StudentModel> GetById(Guid Id)
        {
            return await AC.students
                .SingleAsync(x => x.idstudent == Id);
        }
    }
}
