using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Lab2.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace Lab2.Pages
{
    public class CreateModel : PageModel
    {
        private Stud_Info_Repos Repositary;

        [BindProperty(Name = "data")]
        public Stud_Info Stud { get; set; }

        public CreateModel(Stud_Info_Repos rep)
        {
            Repositary = rep;
            Console.WriteLine($"CreateModel");
        }

        public IActionResult OnPost()
        {
            Console.WriteLine($"OnPost");
            try
            {
                Repositary.Add(Stud);
                Console.WriteLine($"�������� ����� ������� � ������� ������� - {Stud.Id}");
                return RedirectToPage("Index");
            }
            catch (Already_exist ae)
            {
                Console.WriteLine($"������: ����� ������� - {ae.Id}  - ��� ����������");
            }
            return RedirectToPage("Create");
        }
    }
}
