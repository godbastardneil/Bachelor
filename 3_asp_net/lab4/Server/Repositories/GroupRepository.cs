using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Lab4.Server.Data;
using Lab4.Shared.Domain;
using Microsoft.EntityFrameworkCore;

namespace Lab4.Server.Repositories
{

    public class GroupRepository
    {
        private ApplicationDbContext AC;
        public GroupRepository(ApplicationDbContext gc) {
            AC = gc;
        }
        public async Task<IList<GroupModel>> List(string Id)
        {
            return await AC.groups
                .OrderBy(x => x.idgroup)
                .Where(x => x.UserId == Id)
                .ToListAsync();
        }
        public async Task Add(GroupModel data)
        {
            await AC.groups.AddAsync(data);
            await AC.SaveChangesAsync();
        }
        
        public async Task Update(GroupModel data)
        {
            GroupModel up_stud = await AC.groups.SingleAsync(x => x.idgroup == data.idgroup);
            
            up_stud.name = data.name;
            await AC.SaveChangesAsync();
        }
        
        public async Task Remove(Guid group_id)
        {
            GroupModel del_gr = await AC.groups.SingleAsync(x => x.idgroup == group_id);
            
            AC.groups.Remove(del_gr);
            await AC.SaveChangesAsync();
        }

        public async Task<GroupModel> GetById(Guid Id)
        {
            return await AC.groups
                .SingleAsync(x => x.idgroup == Id);
        }
    }
}
