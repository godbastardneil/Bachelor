#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/aspnet:5.0 AS base
WORKDIR /app
EXPOSE 5000
EXPOSE 5001

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build

WORKDIR /src
COPY . .

WORKDIR "/src/Server"
RUN dotnet restore "Lab4.Server.csproj"
RUN dotnet build "Lab4.Server.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "Lab4.Server.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Lab4.Server.dll"]
