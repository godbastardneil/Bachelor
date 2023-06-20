using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using Microsoft.EntityFrameworkCore;

namespace Lab3.Models
{
    public class GroupRepository
    {
        private GroupContext GC;
        public GroupRepository(GroupContext gc) {
            GC = gc;
        }
        public async Task<IList<GroupModel>> List()
        {
            return await GC.group
                .OrderBy(x => x.idgroup)
                .ToListAsync();
        }
        public async Task Add(GroupModel data)
        {
            await GC.group.AddAsync(data);
            await GC.SaveChangesAsync();
        }
        
        public async Task Update(GroupModel data)
        {
            GroupModel up_stud = await GC.group.SingleAsync(x => x.idgroup == data.idgroup);
            
            up_stud.name = data.name;
            await GC.SaveChangesAsync();
        }
        
        public async Task Remove(int group_id)
        {
            GroupModel del_gr = await GC.group.SingleAsync(x => x.idgroup == group_id);
            
            GC.group.Remove(del_gr);
            await GC.SaveChangesAsync();
        }

        public async Task<GroupModel> GetById(int Id)
        {
            return await GC.group
                .SingleAsync(x => x.idgroup == Id);
        }
    }
}
