// Copyright 2010 Hans Pirnay
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Date   : 2010-01-05

#ifndef __PARAMETRICTNLPEXAMPLE_HPP__
#define __PARAMETRICTNLPEXAMPLE_HPP__

#include "IpTNLP.hpp"

namespace Ipopt
{
  
  class ParametricTNLP : public TNLP
  {
  public:

    /** default constructor */
    ParametricTNLP();

    /** default destructor */
    virtual ~ParametricTNLP();

    /**@name Overloaded from TNLP */
    //@{
    /** Method to return some info about the nlp */
    virtual bool get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
			      Index& nnz_h_lag, IndexStyleEnum& index_style);

    /** Method to return the bounds for my problem */
    virtual bool get_bounds_info(Index n, Number* x_l, Number* x_u,
				 Index m, Number* g_l, Number* g_u);

    /** Method to return the starting point for the algorithm */
    virtual bool get_starting_point(Index n, bool init_x, Number* x,
				    bool init_z, Number* z_L, Number* z_U,
				    Index m, bool init_lambda,
				    Number* lambda);

    /** Method to return the objective value */
    virtual bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value);

    /** Method to return the gradient of the objective */
    virtual bool eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f);

    /** Method to return the constraint residuals */
    virtual bool eval_g(Index n, const Number* x, bool new_x, Index m, Number* g);

    /** Method to return:
     *   1) The structure of the jacobian (if "values" is NULL)
     *   2) The values of the jacobian (if "values" is not NULL)
     */
    virtual bool eval_jac_g(Index n, const Number* x, bool new_x,
			    Index m, Index nele_jac, Index* iRow, Index *jCol,
			    Number* values);

    /** Method to return:
     *   1) The structure of the hessian of the lagrangian (if "values" is NULL)
     *   2) The values of the hessian of the lagrangian (if "values" is not NULL)
     */
    virtual bool eval_h(Index n, const Number* x, bool new_x,
			Number obj_factor, Index m, const Number* lambda,
			bool new_lambda, Index nele_hess, Index* iRow,
			Index* jCol, Number* values);

    //@}

    virtual bool get_var_con_metadata(Index n,
                                      StringMetaDataMapType& var_string_md,
                                      IntegerMetaDataMapType& var_integer_md,
                                      NumericMetaDataMapType& var_numeric_md,
                                      Index m,
                                      StringMetaDataMapType& con_string_md,
                                      IntegerMetaDataMapType& con_integer_md,
                                      NumericMetaDataMapType& con_numeric_md);    
    
    /** @name Solution Methods */
    //@{
    /** This method is called when the algorithm is complete so the TNLP can store/write the solution */
    virtual void finalize_solution(SolverReturn status,
				   Index n, const Number* x, const Number* z_L, const Number* z_U,
				   Index m, const Number* g, const Number* lambda,
				   Number obj_value,
				   const IpoptData* ip_data,
				   IpoptCalculatedQuantities* ip_cq);

    /** This method is called just before finalize solution. It returns the parametric solution of the 
     *  dual variables and bound multipliers. */
    virtual void finalize_metadata(Index n,
				   const StringMetaDataMapType& var_string_md,
				   const IntegerMetaDataMapType& var_integer_md,
				   const NumericMetaDataMapType& var_numeric_md,
				   Index m,
				   const StringMetaDataMapType& con_string_md,
				   const IntegerMetaDataMapType& con_integer_md,
				   const NumericMetaDataMapType& con_numeric_md);
    //@}

  private:
    /**@name Methods to block default compiler methods.
     * The compiler automatically generates the following three methods.
     *  Since the default compiler implementation is generally not what
     *  you want (for all but the most simple classes), we usually 
     *  put the declarations of these methods in the private section
     *  and never implement them. This prevents the compiler from
     *  implementing an incorrect "default" behavior without us
     *  knowing. (See Scott Meyers book, "Effective C++")
     *  
     */
    //@{
    ParametricTNLP(const ParametricTNLP&);
    ParametricTNLP& operator=(const ParametricTNLP&);
    //@}


    /* Nominal and perturbed parameter values */
    Number nominal_eta1_;
    Number nominal_eta2_;

    Number eta_1_perturbed_value_;
    Number eta_2_perturbed_value_;
  };

}

#endif
