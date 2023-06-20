using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Lab4.Shared.Domain;
using Lab4.Shared.DTO;

namespace Lab4.Client.Services
{
    public class GroupService
    {
        private readonly HttpClient _http;

        public GroupService(HttpClient http)
        {
            _http = http;
        }
        public async Task<IEnumerable<GroupModel>> GetGroup()
        {
            
            return await _http.GetFromJsonAsync<IEnumerable<GroupModel>>("api/group");
        }

        public async Task<GroupModel> GetGroupById(string id)
        {
            return await _http.GetFromJsonAsync<GroupModel>($"api/group/{id}");
        }

        public async Task<string> GetNameOfGroup(string id)
        {
            GroupModel group = await GetGroupById(id);
            return group.name;
        }

        public async Task CreateGroup(CreateGroupDTO Group)
        {
            var result = await _http.PostAsJsonAsync($"api/group", Group);

            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось добавить группу.");
        }

        public async Task DeleteGroup(GroupModel Group)
        {
            var result = await _http.DeleteAsync($"api/group?id={Group.idgroup}");

            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось удалить группу.");
        }

        public async Task UpdateGroup(GroupModel Group)
        {
            var result = await _http.PatchAsync($"api/group",
                new StringContent(JsonSerializer.Serialize(Group),
                Encoding.UTF8,
                "application/json"));


            if (!result.IsSuccessStatusCode)
                throw new ApplicationException("Не получилось обновить группу.");
        }
    }
}
