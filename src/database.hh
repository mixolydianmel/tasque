#ifndef TASQUE_DATABASE_HH
#define TASQUE_DATABASE_HH

#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <filesystem>
#include <vector>
#include <string>

#include "board.hh"

std::string get_save_dir()
{
    struct passwd *pw = getpwuid(getuid());
    std::string homedir(pw->pw_dir);

    std::filesystem::path savedir(homedir + "/.cache/tasque/");
    if (!(std::filesystem::exists(savedir)))
    {
        std::filesystem::create_directory(savedir);
    }

    std::string savepath = savedir.generic_string() + "data.tsq";
    return savepath;
}

void save_all(const std::vector<Board*> &boards)
{
    std::string savepath = get_save_dir();

    std::ofstream outfile;
    outfile.open(savepath);

    for (size_t i = 0; i < boards.size(); i++)
    {
        Board *b = boards.at(i);
        outfile << "@board " << b->getTitle().c_str() << std::endl;
        for (int i = 0; i < b->getLength(); i++)
        {
            List *l = b->getList(i);
            outfile << "@list " << l->getTitle().c_str() << std::endl;
            for (int j = 0; j < l->getLength(); j++)
            {
                Tile *t = l->getTile(j);
                outfile << "@tile title " << t->getTitle().c_str() << std::endl;
                if (t->getDesc() != "")
                    outfile << "@tile desc " << t->getDesc().c_str() << std::endl;
            }
        }
    }
}

void load(std::vector<Board*> &boards)
{
    std::string savepath = get_save_dir();

    std::ifstream infile;
    infile.open(savepath);

    int currentBoard = -1;
    int currentList = -1;
    int currentTile = -1;

    std::string line;
    while (std::getline(infile, line))
    {
        if (line.find("@board") != std::string::npos)
        {
            std::string title = line.substr(line.find_first_of(" \t") + 1);
            boards.push_back(new Board(title));
            currentBoard++;
            currentList = -1;
            currentTile = -1;
        }
        else if (line.find("@list") != std::string::npos && currentBoard != -1)
        {
            std::string title = line.substr(line.find_first_of(" \t") + 1);
            boards.at(currentBoard)->addList(new List(title));
            currentList++;
            currentTile = -1;
        }
        else if (line.find("@tile title") != std::string::npos && currentBoard != -1 && currentList != -1)
        {
            std::string title = line.substr(line.find_first_of("@tile title \t") + 12);
            boards.at(currentBoard)->getList(currentList)->addTile(new Tile(title));
            currentTile++;
        }
        else if (line.find("@tile desc") != std::string::npos && currentBoard != -1 && currentList != -1 && currentTile != -1)
        {
            std::string desc = line.substr(line.find_first_of("@tile desc \t") + 11);
            boards.at(currentBoard)->getList(currentList)->getTile(currentTile)->setDesc(desc);
        }
    }
}

#endif /* TASQUE_DATABASE_HH */
