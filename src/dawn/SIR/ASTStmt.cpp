//===--------------------------------------------------------------------------------*- C++ -*-===//
//                          _                      
//                         | |                     
//                       __| | __ ___      ___ ___  
//                      / _` |/ _` \ \ /\ / / '_  | 
//                     | (_| | (_| |\ V  V /| | | |
//                      \__,_|\__,_| \_/\_/ |_| |_| - Compiler Toolchain
//
//
//  This file is distributed under the MIT License (MIT). 
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#include "dawn/SIR/ASTExpr.h"
#include "dawn/SIR/ASTStmt.h"
#include "dawn/SIR/ASTVisitor.h"
#include "dawn/SIR/SIR.h"
#include "dawn/Support/Assert.h"
#include "dawn/Support/Casting.h"

namespace dawn {

//===------------------------------------------------------------------------------------------===//
//     BlockStmt
//===------------------------------------------------------------------------------------------===//

BlockStmt::BlockStmt(SourceLocation loc) : Stmt(SK_BlockStmt, loc) {}
BlockStmt::BlockStmt(const std::vector<std::shared_ptr<Stmt>>& statements, SourceLocation loc)
    : Stmt(SK_BlockStmt, loc), statements_(statements) {}

BlockStmt::BlockStmt(const BlockStmt& stmt) : Stmt(SK_BlockStmt, stmt.getSourceLocation()) {
  for(auto s : stmt.getStatements())
    statements_.push_back(s->clone());
}

BlockStmt& BlockStmt::operator=(BlockStmt stmt) {
  assign(stmt);
  statements_ = std::move(stmt.statements_);
  return *this;
}

BlockStmt::~BlockStmt() {}

std::shared_ptr<Stmt> BlockStmt::clone() const { return std::make_shared<BlockStmt>(*this); }

bool BlockStmt::equals(const Stmt* other) const {
  const BlockStmt* otherPtr = dyn_cast<BlockStmt>(other);
  return otherPtr && Stmt::equals(other) && otherPtr->statements_.size() == statements_.size() &&
         std::equal(statements_.begin(), statements_.end(), otherPtr->statements_.begin(),
                    [](const std::shared_ptr<Stmt>& a, const std::shared_ptr<Stmt>& b) {
                      return a->equals(b.get());
                    });
}

void BlockStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<BlockStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     ExprStmt
//===------------------------------------------------------------------------------------------===//

ExprStmt::ExprStmt(const std::shared_ptr<Expr>& expr, SourceLocation loc)
    : Stmt(SK_ExprStmt, loc), expr_(expr) {}

ExprStmt::ExprStmt(const ExprStmt& stmt)
    : Stmt(SK_ExprStmt, stmt.getSourceLocation()), expr_(stmt.getExpr()->clone()) {}

ExprStmt& ExprStmt::operator=(ExprStmt stmt) {
  assign(stmt);
  expr_ = stmt.getExpr();
  return *this;
}

ExprStmt::~ExprStmt() {}

std::shared_ptr<Stmt> ExprStmt::clone() const { return std::make_shared<ExprStmt>(*this); }

bool ExprStmt::equals(const Stmt* other) const {
  const ExprStmt* otherPtr = dyn_cast<ExprStmt>(other);
  return otherPtr && Stmt::equals(other) && expr_->equals(otherPtr->expr_.get());
}

void ExprStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<ExprStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     ReturnStmt
//===------------------------------------------------------------------------------------------===//

ReturnStmt::ReturnStmt(const std::shared_ptr<Expr>& expr, SourceLocation loc)
    : Stmt(SK_ReturnStmt, loc), expr_(expr) {}

ReturnStmt::ReturnStmt(const ReturnStmt& stmt)
    : Stmt(SK_ReturnStmt, stmt.getSourceLocation()), expr_(stmt.getExpr()->clone()) {}

ReturnStmt& ReturnStmt::operator=(ReturnStmt stmt) {
  assign(stmt);
  expr_ = stmt.getExpr();
  return *this;
}

ReturnStmt::~ReturnStmt() {}

std::shared_ptr<Stmt> ReturnStmt::clone() const { return std::make_shared<ReturnStmt>(*this); }

bool ReturnStmt::equals(const Stmt* other) const {
  const ReturnStmt* otherPtr = dyn_cast<ReturnStmt>(other);
  return otherPtr && Stmt::equals(other) && expr_->equals(otherPtr->expr_.get());
}

void ReturnStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<ReturnStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     VarDeclStmt
//===------------------------------------------------------------------------------------------===//

VarDeclStmt::VarDeclStmt(const Type& type, const std::string& name, int dimension, const char* op,
                         std::vector<std::shared_ptr<Expr>> initList, SourceLocation loc)
    : Stmt(SK_VarDeclStmt, loc), type_(type), name_(name), dimension_(dimension), op_(op),
      initList_(std::move(initList)) {}

VarDeclStmt::VarDeclStmt(const VarDeclStmt& stmt)
    : Stmt(SK_VarDeclStmt, stmt.getSourceLocation()), type_(stmt.getType()), name_(stmt.getName()),
      dimension_(stmt.getDimension()), op_(stmt.getOp()) {
  for(const auto& expr : stmt.getInitList())
    initList_.push_back(expr->clone());
}

VarDeclStmt& VarDeclStmt::operator=(VarDeclStmt stmt) {
  assign(stmt);
  type_ = std::move(stmt.getType());
  name_ = std::move(stmt.getName());
  dimension_ = stmt.getDimension();
  op_ = stmt.getOp();
  initList_ = std::move(stmt.getInitList());
  return *this;
}

VarDeclStmt::~VarDeclStmt() {}

std::shared_ptr<Stmt> VarDeclStmt::clone() const { return std::make_shared<VarDeclStmt>(*this); }

bool VarDeclStmt::equals(const Stmt* other) const {
  const VarDeclStmt* otherPtr = dyn_cast<VarDeclStmt>(other);
  return otherPtr && Stmt::equals(other) && type_ == otherPtr->type_ && name_ == otherPtr->name_ &&
         dimension_ == otherPtr->dimension_ && std::strcmp(op_, otherPtr->op_) == 0 &&
         initList_.size() == otherPtr->initList_.size() &&
         std::equal(initList_.begin(), initList_.end(), otherPtr->initList_.begin(),
                    [](const std::shared_ptr<Expr>& a, const std::shared_ptr<Expr>& b) {
                      return a->equals(b.get());
                    });
}

void VarDeclStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<VarDeclStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     VerticalRegionDeclStmt
//===------------------------------------------------------------------------------------------===//

VerticalRegionDeclStmt::VerticalRegionDeclStmt(
    const std::shared_ptr<sir::VerticalRegion>& verticalRegion, SourceLocation loc)
    : Stmt(SK_VerticalRegionDeclStmt, loc), verticalRegion_(verticalRegion) {}

VerticalRegionDeclStmt::VerticalRegionDeclStmt(const VerticalRegionDeclStmt& stmt)
    : Stmt(SK_VerticalRegionDeclStmt, stmt.getSourceLocation()),
      verticalRegion_(stmt.getVerticalRegion()->clone()) {}

VerticalRegionDeclStmt& VerticalRegionDeclStmt::operator=(VerticalRegionDeclStmt stmt) {
  assign(stmt);
  verticalRegion_ = std::move(stmt.getVerticalRegion());
  return *this;
}

VerticalRegionDeclStmt::~VerticalRegionDeclStmt() {}

std::shared_ptr<Stmt> VerticalRegionDeclStmt::clone() const {
  return std::make_shared<VerticalRegionDeclStmt>(*this);
}

bool VerticalRegionDeclStmt::equals(const Stmt* other) const {
  const VerticalRegionDeclStmt* otherPtr = dyn_cast<VerticalRegionDeclStmt>(other);
  // We just compare the shared pointers of the vertical region
  return otherPtr && Stmt::equals(other) && verticalRegion_ == otherPtr->verticalRegion_;
}

void VerticalRegionDeclStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<VerticalRegionDeclStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     StencilCallDeclStmt
//===------------------------------------------------------------------------------------------===//

StencilCallDeclStmt::StencilCallDeclStmt(const std::shared_ptr<sir::StencilCall>& stencilCall,
                                         SourceLocation loc)
    : Stmt(SK_StencilCallDeclStmt, loc), stencilCall_(stencilCall) {}

StencilCallDeclStmt::StencilCallDeclStmt(const StencilCallDeclStmt& stmt)
    : Stmt(SK_StencilCallDeclStmt, stmt.getSourceLocation()),
      stencilCall_(stmt.getStencilCall()->clone()) {}

StencilCallDeclStmt& StencilCallDeclStmt::operator=(StencilCallDeclStmt stmt) {
  assign(stmt);
  stencilCall_ = std::move(stmt.getStencilCall());
  return *this;
}

StencilCallDeclStmt::~StencilCallDeclStmt() {}

std::shared_ptr<Stmt> StencilCallDeclStmt::clone() const {
  return std::make_shared<StencilCallDeclStmt>(*this);
}

bool StencilCallDeclStmt::equals(const Stmt* other) const {
  const StencilCallDeclStmt* otherPtr = dyn_cast<StencilCallDeclStmt>(other);
  // We just compare the shared pointers of the stencil call
  return otherPtr && Stmt::equals(other) && stencilCall_ == otherPtr->stencilCall_;
}

void StencilCallDeclStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<StencilCallDeclStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     BoundaryConditionDeclStmt
//===------------------------------------------------------------------------------------------===//

BoundaryConditionDeclStmt::BoundaryConditionDeclStmt(const std::string& callee, SourceLocation loc)
    : Stmt(SK_BoundaryConditionDeclStmt, loc), functor_(callee) {}

BoundaryConditionDeclStmt::BoundaryConditionDeclStmt(const BoundaryConditionDeclStmt& stmt)
    : Stmt(SK_BoundaryConditionDeclStmt, stmt.getSourceLocation()), functor_(stmt.functor_),
      fields_(stmt.fields_) {}

BoundaryConditionDeclStmt& BoundaryConditionDeclStmt::operator=(BoundaryConditionDeclStmt stmt) {
  assign(stmt);
  functor_ = std::move(stmt.functor_);
  fields_ = std::move(stmt.fields_);
  return *this;
}

BoundaryConditionDeclStmt::~BoundaryConditionDeclStmt() {}

std::shared_ptr<Stmt> BoundaryConditionDeclStmt::clone() const {
  return std::make_shared<BoundaryConditionDeclStmt>(*this);
}

bool BoundaryConditionDeclStmt::equals(const Stmt* other) const {
  const BoundaryConditionDeclStmt* otherPtr = dyn_cast<BoundaryConditionDeclStmt>(other);
  return otherPtr && Stmt::equals(other) && functor_ == otherPtr->functor_ &&
         fields_.size() == otherPtr->fields_.size() &&
         std::equal(fields_.begin(), fields_.end(), otherPtr->fields_.begin(),
                    [](const std::shared_ptr<sir::Field>& a, const std::shared_ptr<sir::Field>& b) {
                      return a->Name == b->Name && a->IsTemporary == b->IsTemporary;
                    });
}

void BoundaryConditionDeclStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<BoundaryConditionDeclStmt>(shared_from_this()));
}

//===------------------------------------------------------------------------------------------===//
//     IfStmt
//===------------------------------------------------------------------------------------------===//

IfStmt::IfStmt(const std::shared_ptr<Stmt>& condStmt, const std::shared_ptr<Stmt>& thenStmt,
               const std::shared_ptr<Stmt>& elseStmt, SourceLocation loc)
    : Stmt(SK_IfStmt, loc), subStmts_{condStmt, thenStmt, elseStmt} {}

IfStmt::IfStmt(const IfStmt& stmt)
    : Stmt(SK_IfStmt, stmt.getSourceLocation()),
      subStmts_{stmt.getCondStmt()->clone(), stmt.getThenStmt()->clone(),
                stmt.hasElse() ? stmt.getElseStmt()->clone() : nullptr} {}

IfStmt& IfStmt::operator=(IfStmt stmt) {
  assign(stmt);
  subStmts_[OK_Cond] = std::move(stmt.getCondStmt());
  subStmts_[OK_Then] = std::move(stmt.getThenStmt());
  subStmts_[OK_Else] = std::move(stmt.getElseStmt());
  return *this;
}

IfStmt::~IfStmt() {}

std::shared_ptr<Stmt> IfStmt::clone() const { return std::make_shared<IfStmt>(*this); }

bool IfStmt::equals(const Stmt* other) const {
  const IfStmt* otherPtr = dyn_cast<IfStmt>(other);
  return otherPtr && Stmt::equals(other) &&
         subStmts_[OK_Cond]->equals(otherPtr->subStmts_[OK_Cond].get()) &&
         subStmts_[OK_Then]->equals(otherPtr->subStmts_[OK_Then].get()) &&
         subStmts_[OK_Else]->equals(otherPtr->subStmts_[OK_Else].get());
}

void IfStmt::accept(ASTVisitor& visitor) {
  visitor.visit(std::static_pointer_cast<IfStmt>(shared_from_this()));
}

} // namespace dawn
