#ifndef GLMNET_H_
#define GLMNET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 INPUT

 c   parm = penalty member index (0 <= parm <= 1)
 c        = 0.0 => ridge
 c        = 1.0 => lasso

 c   no = number of observations

 c   ni = number of predictor variables

 c   nc = number of classes (distinct outcome values)
 c        nc=1 => binomial two-class logistic regression
 c            (all output references class 1)

 c   x(no,ni) = predictor data matrix flat file (overwritten)

 c   y(no,max(2,nc)) = number of each class at each design point(overwritten)

 c   g(no,nc) = observation off-sets for each class

 c   jd(jd(1)+1) = predictor variable deletion flag
 c      jd(1) = 0  => use all variables
 c      jd(1) != 0 => do not use variables jd(2)...jd(jd(1)+1)

 c   vp(ni) = relative penalties for each predictor variable
 c      vp(j) = 0 => jth variable unpenalized

 c   cl(2,ni) = interval constraints on coefficient values (overwritten)
 c      cl(1,j) = lower bound for jth coefficient value (<= 0.0)
 c      cl(2,j) = upper bound for jth coefficient value (>= 0.0)

 c   ne = maximum number of variables allowed to enter largest model
 c        (stopping criterion)

 c   nx = maximum number of variables allowed to enter all models
 c        along path (memory allocation, nx > ne).

 c   nlam = (maximum) number of lamda values

 c   flmin = user control of lamda values (>=0)
 c      flmin < 1.0 => minimum lamda = flmin*(largest lamda value)
 c      flmin >= 1.0 => use supplied lamda values (see below)

 c   ulam(nlam) = user supplied lamda values (ignored if flmin < 1.0)

 c   thr = convergence threshold for each lamda solution.
 c      iterations stop when the maximum reduction in the criterion value
 c      as a result of each parameter update over a single pass
 c      is less than thr times the null criterion value.
 c      (suggested value, thr=1.0e-5)

 c   isd = predictor variable standarization flag:
 c      isd = 0 => regression on original predictor variables
 c      isd = 1 => regression on standardized predictor variables
 c      Note: output solutions always reference original
 c            variables locations and scales.

 c   intr = intercept flag
 c      intr = 0/1 => don't/do include intercept in model

 c   maxit = maximum allowed number of passes over the data for all lambda
 c      values (suggested values, maxit = 100000)

 c   kopt = optimization flag
 c      kopt = 0 => Newton-Raphson (recommended)
 c      kpot = 1 => modified Newton-Raphson (sometimes faster)
 c      kpot = 2 => nonzero coefficients same for each class (nc > 1)

 OUTPUT

 c   lmu = actual number of lamda values (solutions)

 c   a0(nc,lmu) = intercept values for each class at each solution

 c   ca(nx,nc,lmu) = compressed coefficient values for each class at
 c                each solution

 c   ia(nx) = pointers to compressed coefficients

 c   nin(lmu) = number of compressed coefficients for each solution

 c   dev0 = null deviance (intercept only model)

 c   dev(lmu) = fraction of devience explained by each solution

 c   alm(lmu) = lamda values corresponding to each solution

 c   nlp = actual number of passes over the data for all lamda values

 c   jerr = error flag
 c      jerr = 0  => no error
 c      jerr > 0 => fatal error - no output returned
 c         jerr < 7777 => memory allocation error
 c         jerr = 7777 => all used predictors have zero variance
 c         jerr = 8000 + k => null probability < 1.0e-5 for class k
 c         jerr = 9000 + k => null probability for class k
 c                            > 1.0 - 1.0e-5
 c         jerr = 10000 => maxval(vp) <= 0.0
 c         jerr = 90000 => bounds adjustment non convergence
 C      jerr < 0 => non fatal error - partial output:
 c         Solutions for larger lamdas (1:(k-1)) returned.
 c         jerr = -k => convergence for kth lamda value not reached
 c            after maxit (see above) iterations.
 c         jerr = -10000-k => number of non zero coefficients along path
 c            exceeds nx (see above) at kth lamda value.
 c         jerr = -20000-k => max(p*(1-p)) < 1.0e-6 at kth lamda value.

 c    g(no,nc) = training data values for last (lmu_th) solution linear
 c               combination.
 */
void lognet_(float *parm, int *no, int *ni, int *nc, float *x, float *y,
		float *g, int *jd, float *vp, float *cl, int *ne, int *nx, int *nlam,
		float *flmin, float *ulam, float *thr, int *isd, int *intr, int *maxit,
		int *kopt, int *lmu, float *a0, float *ca, int *ia, int *nin,
		float *dev0, float *dev, float *alm, int *nlp, int *jerr);



#ifdef __cplusplus
}
#endif

#endif // GLMNET_H_
