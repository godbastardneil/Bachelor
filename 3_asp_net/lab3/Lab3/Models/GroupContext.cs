using System;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Models
{
    public class GroupContext: DbContext
    {
        public DbSet<GroupModel> group { get; set; }
        public DbSet<StudentModel> student { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder options)
            => options.UseNpgsql("host=db;Database=asp_net_lab3;Username=postgres;Password=postgres1!");
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<StudentModel>()
                .HasOne<GroupModel>()
                .WithMany()
                .HasForeignKey(p => p.idgroup)
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<GroupModel>().HasData(
                new GroupModel { idgroup = 1, name = "ДИПРБ 1" },
                new GroupModel { idgroup = 2, name = "ДИПРБ 2" }
            );
            
            modelBuilder.Entity<StudentModel>().HasData(
                new StudentModel { idstudent = 1824, FIO = "студент1", headman_sign = true, idgroup = 1 },
                new StudentModel { idstudent = 7178, FIO = "студент2", headman_sign = false, idgroup = 1 },
                new StudentModel { idstudent = 78783, FIO = "студент3", headman_sign = true, idgroup = 2 },
                new StudentModel { idstudent = 78785, FIO = "студент4", headman_sign = false, idgroup = 2 }
            );
        }
    }
}
