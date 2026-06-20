#pragma once

struct PageNavigationContent {
    int currentPage = 0;
    int maxPage = 0;

    PageNavigationContent(int currentPage, int maxPage): currentPage(currentPage), maxPage(maxPage) {}
};
