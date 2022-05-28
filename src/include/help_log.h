/**
 * @file help_log.h
 * @author kate (zanetty54@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef HELP_LOG_HH
#define HELP_LOG_HH

#include <graph.h>

//- Print whole adjancecy list
//- Print adjacents of given vertex

std::ostream& operator<<(std::ostream& _cout, const graph& _graph)
{
    for (int i = 0; i < _graph.grade(); ++i)
    {
        std:cout << "adjacents of vertex: (" << i << "): ";
        for (const auto vertex : _graph.graph[i])
            std::cout << "[" << vertex << "] ";
        std::cout << endl;
    }

    return _cout;
}

#endif  //END OF HELP_LOG_HH