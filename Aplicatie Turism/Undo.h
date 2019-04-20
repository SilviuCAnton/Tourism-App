#pragma once
#include "Repository.h"
class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual std::unique_ptr<UndoAction> clone() const = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
private:
	Repository& repo;
	Offer addedOffer;
public:
	UndoAdd(Repository& repo, Offer offer);
	void doUndo() override;
	void doRedo() override;
	std::unique_ptr<UndoAction> clone() const override;
};

class UndoRemove : public UndoAction {
private:
	Repository& repo;
	Offer removedOffer;
public:
	UndoRemove(Repository& repo, Offer offer);
	void doUndo() override;
	void doRedo() override;
	std::unique_ptr<UndoAction> clone() const override;
};

class UndoModify : public UndoAction {
private:
	Repository& repo;
	Offer originalOffer;
	Offer modifiedOffer;
public:
	UndoModify(Repository& repo, Offer originalOffer, Offer modifiedOffer);
	void doUndo() override;
	void doRedo() override;
	std::unique_ptr<UndoAction> clone() const override;
};