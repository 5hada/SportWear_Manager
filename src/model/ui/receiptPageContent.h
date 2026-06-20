#pragma once

#include "model/product/receipt.h"
#include "model/ui/pageNavigationContent.h"

#include <string>
#include <vector>
#include <utility>

using std::string;

struct ReceiptRowContent {
    int id = -1;
    string date;
    string itemSummary;
    int paid = 0;
    string status;
    bool refundable = false;

    ReceiptRowContent(int id, string date, string itemSummary, int paid, bool canceled):
        id(id),
        date(std::move(date)),
        itemSummary(std::move(itemSummary)),
        paid(paid),
        status(canceled ? "Canceled" : "Paid"),
        refundable(!canceled) {}
    ReceiptRowContent(const Receipt& receipt, string itemSummary):
        ReceiptRowContent(receipt.getId(), receipt.getDate(), std::move(itemSummary), receipt.getPaid(), receipt.getIsCanceled()) {}
};

struct ReceiptPageContent {
    PageNavigationContent indexData;
    std::vector<ReceiptRowContent> rows;

    ReceiptPageContent(PageNavigationContent indexData): indexData(indexData) {}

    ReceiptPageContent& operator<<(const ReceiptRowContent& row) {
        rows.push_back(row);
        return *this;
    }
};
