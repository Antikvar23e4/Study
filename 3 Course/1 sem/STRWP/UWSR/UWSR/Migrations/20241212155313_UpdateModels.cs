using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace UWSR.Migrations
{
    /// <inheritdoc />
    public partial class UpdateModels : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Rating",
                table: "Links",
                newName: "UselessCount");

            migrationBuilder.AddColumn<int>(
                name: "UsefulCount",
                table: "Links",
                type: "int",
                nullable: false,
                defaultValue: 0);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "UsefulCount",
                table: "Links");

            migrationBuilder.RenameColumn(
                name: "UselessCount",
                table: "Links",
                newName: "Rating");
        }
    }
}
