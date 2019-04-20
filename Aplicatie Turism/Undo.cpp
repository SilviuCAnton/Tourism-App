#include "Undo.h"

UndoAdd::UndoAdd(Repository & repo, Offer offer) : repo{ repo }, addedOffer{ offer } {
}

void UndoAdd::doUndo() {
}

void UndoAdd::doRedo() {
}

UndoRemove::UndoRemove(Repository & repo, Offer offer) : repo{ repo }, removedOffer{ offer } {
}

void UndoRemove::doUndo() {
}

void UndoRemove::doRedo() {
}

UndoModify::UndoModify(Repository & repo, Offer originalOffer, Offer modifiedOffer) : repo{ repo }, originalOffer{ originalOffer }, modifiedOffer{ modifiedOffer } {
}

void UndoModify::doUndo() {
}

void UndoModify::doRedo() {
}
