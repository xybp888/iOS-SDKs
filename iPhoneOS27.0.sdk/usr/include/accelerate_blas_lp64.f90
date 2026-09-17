! Fortran 90 interfaces to Apple Accelerate BLAS (LP64).
!
! Integer arguments use default integer (4 bytes).
! Binds to the ACCELERATE_NEW_LAPACK symbols via the $NEWLAPACK suffix.
!
! Usage:
!   use accelerate_blas_lp64
!   call dgemm('N', 'N', m, n, k, alpha, a, lda, b, ldb, beta, c, ldc)

module accelerate_blas_lp64
  implicit none

  interface

    subroutine xerbla(srname, info) &
      bind(C, name='xerbla$NEWLAPACK')
      character, intent(inout) :: srname
      integer, intent(inout) :: info
    end subroutine xerbla

    integer function isamax(N, X, INCX) &
      bind(C, name='isamax$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
    end function isamax

    integer function idamax(N, X, INCX) &
      bind(C, name='idamax$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
    end function idamax

    integer function icamax(N, X, INCX) &
      bind(C, name='icamax$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function icamax

    integer function izamax(N, X, INCX) &
      bind(C, name='izamax$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function izamax

    real function sasum(N, X, INCX) &
      bind(C, name='sasum$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
    end function sasum

    double precision function dasum(N, X, INCX) &
      bind(C, name='dasum$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
    end function dasum

    real function scasum(N, X, INCX) &
      bind(C, name='scasum$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function scasum

    double precision function dzasum(N, X, INCX) &
      bind(C, name='dzasum$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function dzasum

    subroutine saxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='saxpy$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine saxpy

    subroutine daxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='daxpy$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine daxpy

    subroutine caxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='caxpy$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine caxpy

    subroutine zaxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='zaxpy$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zaxpy

    subroutine saxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='saxpby$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine saxpby

    subroutine daxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='daxpby$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine daxpby

    subroutine caxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='caxpby$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine caxpby

    subroutine zaxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zaxpby$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zaxpby

    subroutine scopy(N, X, INCX, Y, INCY) &
      bind(C, name='scopy$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine scopy

    subroutine dcopy(N, X, INCX, Y, INCY) &
      bind(C, name='dcopy$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dcopy

    subroutine ccopy(N, X, INCX, Y, INCY) &
      bind(C, name='ccopy$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine ccopy

    subroutine zcopy(N, X, INCX, Y, INCY) &
      bind(C, name='zcopy$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zcopy

    real function sdot(N, X, INCX, Y, INCY) &
      bind(C, name='sdot$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
    end function sdot

    double precision function ddot(N, X, INCX, Y, INCY) &
      bind(C, name='ddot$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: Y
      integer, intent(in) :: INCY
    end function ddot

    subroutine cdotu(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='cdotu$NEWLAPACK')
      complex, intent(inout) :: ret_val
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
    end subroutine cdotu

    subroutine zdotu(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='zdotu$NEWLAPACK')
      double complex, intent(inout) :: ret_val
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
    end subroutine zdotu

    subroutine cdotc(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='cdotc$NEWLAPACK')
      complex, intent(inout) :: ret_val
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
    end subroutine cdotc

    subroutine zdotc(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='zdotc$NEWLAPACK')
      double complex, intent(inout) :: ret_val
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
    end subroutine zdotc

    real function sdsdot(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='sdsdot$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
    end function sdsdot

    double precision function dsdot(N, X, INCX, Y, INCY) &
      bind(C, name='dsdot$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
    end function dsdot

    real function snrm2(N, X, INCX) &
      bind(C, name='snrm2$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: X
      integer, intent(in) :: INCX
    end function snrm2

    double precision function dnrm2(N, X, INCX) &
      bind(C, name='dnrm2$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
    end function dnrm2

    real function scnrm2(N, X, INCX) &
      bind(C, name='scnrm2$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function scnrm2

    double precision function dznrm2(N, X, INCX) &
      bind(C, name='dznrm2$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
    end function dznrm2

    subroutine srot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='srot$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(inout) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
      real, intent(in) :: C
      real, intent(in) :: S
    end subroutine srot

    subroutine drot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='drot$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
      double precision, intent(in) :: C
      double precision, intent(in) :: S
    end subroutine drot

    subroutine csrot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='csrot$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
      real, intent(in) :: C
      real, intent(in) :: S
    end subroutine csrot

    subroutine zdrot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='zdrot$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
      double precision, intent(in) :: C
      double precision, intent(in) :: S
    end subroutine zdrot

    subroutine srotg(A, B, C, S) &
      bind(C, name='srotg$NEWLAPACK')
      real, intent(inout) :: A
      real, intent(inout) :: B
      real, intent(inout) :: C
      real, intent(inout) :: S
    end subroutine srotg

    subroutine drotg(A, B, C, S) &
      bind(C, name='drotg$NEWLAPACK')
      double precision, intent(inout) :: A
      double precision, intent(inout) :: B
      double precision, intent(inout) :: C
      double precision, intent(inout) :: S
    end subroutine drotg

    subroutine crotg(A, B, C, S) &
      bind(C, name='crotg$NEWLAPACK')
      complex, intent(inout) :: A
      complex, intent(inout) :: B
      real, intent(inout) :: C
      complex, intent(inout) :: S
    end subroutine crotg

    subroutine zrotg(A, B, C, S) &
      bind(C, name='zrotg$NEWLAPACK')
      double complex, intent(inout) :: A
      double complex, intent(inout) :: B
      double precision, intent(inout) :: C
      double complex, intent(inout) :: S
    end subroutine zrotg

    subroutine srotm(N, X, INCX, Y, INCY, PARAM) &
      bind(C, name='srotm$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(inout) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
      real, intent(in) :: PARAM
    end subroutine srotm

    subroutine drotm(N, X, INCX, Y, INCY, PARAM) &
      bind(C, name='drotm$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
      double precision, intent(in) :: PARAM
    end subroutine drotm

    subroutine srotmg(D1, D2, X1, Y1, PARAM) &
      bind(C, name='srotmg$NEWLAPACK')
      real, intent(inout) :: D1
      real, intent(inout) :: D2
      real, intent(inout) :: X1
      real, intent(in) :: Y1
      real, intent(inout) :: PARAM
    end subroutine srotmg

    subroutine drotmg(D1, D2, X1, Y1, PARAM) &
      bind(C, name='drotmg$NEWLAPACK')
      double precision, intent(inout) :: D1
      double precision, intent(inout) :: D2
      double precision, intent(inout) :: X1
      double precision, intent(in) :: Y1
      double precision, intent(inout) :: PARAM
    end subroutine drotmg

    subroutine sscal(N, ALPHA, X, INCX) &
      bind(C, name='sscal$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine sscal

    subroutine dscal(N, ALPHA, X, INCX) &
      bind(C, name='dscal$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dscal

    subroutine cscal(N, ALPHA, X, INCX) &
      bind(C, name='cscal$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine cscal

    subroutine zscal(N, ALPHA, X, INCX) &
      bind(C, name='zscal$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine zscal

    subroutine csscal(N, ALPHA, X, INCX) &
      bind(C, name='csscal$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine csscal

    subroutine zdscal(N, ALPHA, X, INCX) &
      bind(C, name='zdscal$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine zdscal

    subroutine sswap(N, X, INCX, Y, INCY) &
      bind(C, name='sswap$NEWLAPACK')
      integer, intent(in) :: N
      real, intent(inout) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine sswap

    subroutine dswap(N, X, INCX, Y, INCY) &
      bind(C, name='dswap$NEWLAPACK')
      integer, intent(in) :: N
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dswap

    subroutine cswap(N, X, INCX, Y, INCY) &
      bind(C, name='cswap$NEWLAPACK')
      integer, intent(in) :: N
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine cswap

    subroutine zswap(N, X, INCX, Y, INCY) &
      bind(C, name='zswap$NEWLAPACK')
      integer, intent(in) :: N
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zswap

    subroutine sgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='sgemv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine sgemv

    subroutine dgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dgemv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dgemv

    subroutine cgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='cgemv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine cgemv

    subroutine zgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zgemv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zgemv

    subroutine sgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='sgbmv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: KL
      integer, intent(in) :: KU
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine sgbmv

    subroutine dgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dgbmv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: KL
      integer, intent(in) :: KU
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dgbmv

    subroutine cgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='cgbmv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: KL
      integer, intent(in) :: KU
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine cgbmv

    subroutine zgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zgbmv$NEWLAPACK')
      character, intent(in) :: TRANS
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: KL
      integer, intent(in) :: KU
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zgbmv

    subroutine sger(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='sger$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
      real, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine sger

    subroutine dger(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='dger$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: Y
      integer, intent(in) :: INCY
      double precision, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine dger

    subroutine cgerc(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cgerc$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
      complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine cgerc

    subroutine zgerc(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zgerc$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
      double complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine zgerc

    subroutine cgeru(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cgeru$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
      complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine cgeru

    subroutine zgeru(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zgeru$NEWLAPACK')
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
      double complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine zgeru

    subroutine chbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='chbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine chbmv

    subroutine zhbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zhbmv

    subroutine chemv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='chemv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine chemv

    subroutine zhemv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhemv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zhemv

    subroutine cher(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='cher$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine cher

    subroutine zher(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='zher$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine zher

    subroutine cher2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cher2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
      complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine cher2

    subroutine zher2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zher2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
      double complex, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine zher2

    subroutine chpmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='chpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: AP
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine chpmv

    subroutine zhpmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: AP
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine zhpmv

    subroutine chpr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='chpr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(inout) :: AP
    end subroutine chpr

    subroutine zhpr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='zhpr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(inout) :: AP
    end subroutine zhpr

    subroutine chpr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='chpr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer, intent(in) :: INCX
      complex, intent(in) :: Y
      integer, intent(in) :: INCY
      complex, intent(inout) :: AP
    end subroutine chpr2

    subroutine zhpr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='zhpr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer, intent(in) :: INCX
      double complex, intent(in) :: Y
      integer, intent(in) :: INCY
      double complex, intent(inout) :: AP
    end subroutine zhpr2

    subroutine ssbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='ssbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine ssbmv

    subroutine dsbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dsbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dsbmv

    subroutine sspmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='sspmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: AP
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine sspmv

    subroutine dspmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='dspmv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: AP
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dspmv

    subroutine sspr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='sspr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: AP
    end subroutine sspr

    subroutine dspr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='dspr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: AP
    end subroutine dspr

    subroutine sspr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='sspr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
      real, intent(inout) :: AP
    end subroutine sspr2

    subroutine dspr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='dspr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: Y
      integer, intent(in) :: INCY
      double precision, intent(inout) :: AP
    end subroutine dspr2

    subroutine ssymv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='ssymv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine ssymv

    subroutine dsymv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dsymv$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer, intent(in) :: INCY
    end subroutine dsymv

    subroutine ssyr(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='ssyr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine ssyr

    subroutine dsyr(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='dsyr$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine dsyr

    subroutine ssyr2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='ssyr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer, intent(in) :: INCX
      real, intent(in) :: Y
      integer, intent(in) :: INCY
      real, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine ssyr2

    subroutine dsyr2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='dsyr2$NEWLAPACK')
      character, intent(in) :: UPLO
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer, intent(in) :: INCX
      double precision, intent(in) :: Y
      integer, intent(in) :: INCY
      double precision, intent(inout) :: A
      integer, intent(in) :: LDA
    end subroutine dsyr2

    subroutine stbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='stbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine stbmv

    subroutine dtbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='dtbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtbmv

    subroutine ctbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ctbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctbmv

    subroutine ztbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ztbmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztbmv

    subroutine stbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='stbsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine stbsv

    subroutine dtbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='dtbsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtbsv

    subroutine ctbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ctbsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctbsv

    subroutine ztbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ztbsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztbsv

    subroutine stpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='stpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      real, intent(in) :: AP
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine stpmv

    subroutine dtpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='dtpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double precision, intent(in) :: AP
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtpmv

    subroutine ctpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ctpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      complex, intent(in) :: AP
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctpmv

    subroutine ztpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ztpmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double complex, intent(in) :: AP
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztpmv

    subroutine stpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='stpsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      real, intent(in) :: AP
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine stpsv

    subroutine dtpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='dtpsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double precision, intent(in) :: AP
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtpsv

    subroutine ctpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ctpsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      complex, intent(in) :: AP
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctpsv

    subroutine ztpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ztpsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double complex, intent(in) :: AP
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztpsv

    subroutine strmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='strmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine strmv

    subroutine dtrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='dtrmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtrmv

    subroutine ctrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ctrmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctrmv

    subroutine ztrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ztrmv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztrmv

    subroutine strsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='strsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine strsv

    subroutine dtrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='dtrsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine dtrsv

    subroutine ctrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ctrsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ctrsv

    subroutine ztrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ztrsv$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer, intent(in) :: N
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: X
      integer, intent(in) :: INCX
    end subroutine ztrsv

    subroutine sgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='sgemm$NEWLAPACK')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: B
      integer, intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine sgemm

    subroutine dgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dgemm$NEWLAPACK')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: B
      integer, intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine dgemm

    subroutine cgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='cgemm$NEWLAPACK')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: B
      integer, intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine cgemm

    subroutine zgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zgemm$NEWLAPACK')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer, intent(in) :: M
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: B
      integer, intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zgemm

    subroutine chemm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='chemm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: B
      integer, intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine chemm

    subroutine zhemm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zhemm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: B
      integer, intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zhemm

    subroutine cherk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='cherk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine cherk

    subroutine zherk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='zherk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zherk

    subroutine cher2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='cher2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: B
      integer, intent(in) :: LDB
      real, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine cher2k

    subroutine zher2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zher2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: B
      integer, intent(in) :: LDB
      double precision, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zher2k

    subroutine ssymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='ssymm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: B
      integer, intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine ssymm

    subroutine dsymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dsymm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: B
      integer, intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine dsymm

    subroutine csymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='csymm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: B
      integer, intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine csymm

    subroutine zsymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zsymm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: B
      integer, intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zsymm

    subroutine ssyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='ssyrk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine ssyrk

    subroutine dsyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='dsyrk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine dsyrk

    subroutine csyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='csyrk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine csyrk

    subroutine zsyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='zsyrk$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zsyrk

    subroutine ssyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='ssyr2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(in) :: B
      integer, intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine ssyr2k

    subroutine dsyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dsyr2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(in) :: B
      integer, intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine dsyr2k

    subroutine csyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='csyr2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(in) :: B
      integer, intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine csyr2k

    subroutine zsyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zsyr2k$NEWLAPACK')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer, intent(in) :: N
      integer, intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(in) :: B
      integer, intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer, intent(in) :: LDC
    end subroutine zsyr2k

    subroutine strmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='strmm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine strmm

    subroutine dtrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='dtrmm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine dtrmm

    subroutine ctrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ctrmm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine ctrmm

    subroutine ztrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ztrmm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine ztrmm

    subroutine strsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='strsm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer, intent(in) :: LDA
      real, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine strsm

    subroutine dtrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='dtrsm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer, intent(in) :: LDA
      double precision, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine dtrsm

    subroutine ctrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ctrsm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer, intent(in) :: LDA
      complex, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine ctrsm

    subroutine ztrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ztrsm$NEWLAPACK')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer, intent(in) :: M
      integer, intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer, intent(in) :: LDA
      double complex, intent(inout) :: B
      integer, intent(in) :: LDB
    end subroutine ztrsm

  end interface

end module accelerate_blas_lp64
