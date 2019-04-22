#include "Undo.h"

UndoAdd::UndoAdd(Repository & repo, Offer offer) : repo{ repo }, addedOffer{ offer } {
}

void UndoAdd::doUndo() {
	repo.deleteElement(addedOffer.getId());
}

void UndoAdd::doRedo() {
	repo.store(addedOffer);
}

UndoRemove::UndoRemove(Repository & repo, Offer offer) : repo{ repo }, removedOffer{ offer } {
}

void UndoRemove::doUndo() {
	repo.store(removedOffer);
}

void UndoRemove::doRedo() {
	repo.deleteElement(removedOffer.getId());
}

UndoModify::UndoModify(Repository & repo, Offer originalOffer, Offer modifiedOffer) : repo{ repo }, originalOffer{ originalOffer }, modifiedOffer{ modifiedOffer } {
}

void UndoModify::doUndo() {
	repo.update(originalOffer);
}

void UndoModify::doRedo() {
	repo.update(modifiedOffer);
}
