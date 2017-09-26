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

#ifndef DAWN_CODEGEN_ASTCODEGENGTCLANGSTENCILDESC_H
#define DAWN_CODEGEN_ASTCODEGENGTCLANGSTENCILDESC_H

#include "dawn/CodeGen/ASTCodeGenCXX.h"
#include "dawn/Support/StringUtil.h"
#include <stack>
#include <unordered_map>

namespace dawn {

class StencilInstantiation;

/// @brief ASTVisitor to generate C++ gridtools code for the stencil and stencil function bodies
/// @ingroup codegen
class ASTCodeGenGTClangStencilDesc : public ASTCodeGenCXX {
protected:
  const StencilInstantiation* instantiation_;

  /// StencilID to the name of the generated stencils for this ID
  const std::unordered_map<int, std::vector<std::string>>& StencilIDToStencilNameMap_;

public:
  using Base = ASTCodeGenCXX;

  ASTCodeGenGTClangStencilDesc(
      const StencilInstantiation* instantiation,
      const std::unordered_map<int, std::vector<std::string>>& StencilIDToStencilNameMap);
  virtual ~ASTCodeGenGTClangStencilDesc();

  /// @name Statement implementation
  /// @{
  virtual void visit(const std::shared_ptr<BlockStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<ExprStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<ReturnStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<VarDeclStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<VerticalRegionDeclStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<StencilCallDeclStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<BoundaryConditionDeclStmt>& stmt) override;
  virtual void visit(const std::shared_ptr<IfStmt>& stmt) override;
  /// @}

  /// @name Expression implementation
  /// @{
  virtual void visit(const std::shared_ptr<UnaryOperator>& expr) override;
  virtual void visit(const std::shared_ptr<BinaryOperator>& expr) override;
  virtual void visit(const std::shared_ptr<AssignmentExpr>& expr) override;
  virtual void visit(const std::shared_ptr<TernaryOperator>& expr) override;
  virtual void visit(const std::shared_ptr<FunCallExpr>& expr) override;
  virtual void visit(const std::shared_ptr<StencilFunCallExpr>& expr) override;
  virtual void visit(const std::shared_ptr<StencilFunArgExpr>& expr) override;
  virtual void visit(const std::shared_ptr<VarAccessExpr>& expr) override;
  virtual void visit(const std::shared_ptr<LiteralAccessExpr>& expr) override;
  virtual void visit(const std::shared_ptr<FieldAccessExpr>& expr) override;
  /// @}

  const std::string& getName(const std::shared_ptr<Stmt>& stmt) const override;
  const std::string& getName(const std::shared_ptr<Expr>& expr) const override;
};

} // namespace dawn

#endif
