using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

namespace Lab3.Migrations
{
    public partial class MyFirstMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "group",
                columns: table => new
                {
                    idgroup = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    name = table.Column<string>(type: "text", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_group", x => x.idgroup);
                });

            migrationBuilder.CreateTable(
                name: "student",
                columns: table => new
                {
                    idstudent = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    FIO = table.Column<string>(type: "text", nullable: true),
                    headman_sign = table.Column<bool>(type: "boolean", nullable: false),
                    idgroup = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_student", x => x.idstudent);
                    table.ForeignKey(
                        name: "FK_student_group_idgroup",
                        column: x => x.idgroup,
                        principalTable: "group",
                        principalColumn: "idgroup",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "group",
                columns: new[] { "idgroup", "name" },
                values: new object[,]
                {
                    { 1, "ДИПРБ 1" },
                    { 2, "ДИПРБ 2" }
                });

            migrationBuilder.InsertData(
                table: "student",
                columns: new[] { "idstudent", "FIO", "headman_sign", "idgroup" },
                values: new object[,]
                {
                    { 1824, "студент1", true, 1 },
                    { 7178, "студент2", false, 1 },
                    { 78783, "студент3", true, 2 },
                    { 78785, "студент4", false, 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_student_idgroup",
                table: "student",
                column: "idgroup");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "student");

            migrationBuilder.DropTable(
                name: "group");
        }
    }
}
