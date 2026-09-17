! Fortran 90 interfaces to Apple Accelerate BLAS (ILP64).
!
! Integer arguments use integer(8) (8 bytes) for large problem sizes.
! Binds to the ACCELERATE_NEW_LAPACK symbols via the $NEWLAPACK$ILP64 suffix.
!
! Usage:
!   use accelerate_blas_ilp64
!   integer(8) :: m, n, k, lda, ldb, ldc
!   call dgemm('N', 'N', m, n, k, alpha, a, lda, b, ldb, beta, c, ldc)

module accelerate_blas_ilp64
  implicit none

  interface

    subroutine xerbla(srname, info) &
      bind(C, name='xerbla$NEWLAPACK$ILP64')
      character, intent(inout) :: srname
      integer(8), intent(inout) :: info
    end subroutine xerbla

    integer(8) function isamax(N, X, INCX) &
      bind(C, name='isamax$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function isamax

    integer(8) function idamax(N, X, INCX) &
      bind(C, name='idamax$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function idamax

    integer(8) function icamax(N, X, INCX) &
      bind(C, name='icamax$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function icamax

    integer(8) function izamax(N, X, INCX) &
      bind(C, name='izamax$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function izamax

    real function sasum(N, X, INCX) &
      bind(C, name='sasum$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function sasum

    double precision function dasum(N, X, INCX) &
      bind(C, name='dasum$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function dasum

    real function scasum(N, X, INCX) &
      bind(C, name='scasum$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function scasum

    double precision function dzasum(N, X, INCX) &
      bind(C, name='dzasum$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function dzasum

    subroutine saxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='saxpy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine saxpy

    subroutine daxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='daxpy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine daxpy

    subroutine caxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='caxpy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine caxpy

    subroutine zaxpy(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='zaxpy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zaxpy

    subroutine saxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='saxpby$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine saxpby

    subroutine daxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='daxpby$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine daxpby

    subroutine caxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='caxpby$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine caxpby

    subroutine zaxpby(N, ALPHA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zaxpby$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zaxpby

    subroutine scopy(N, X, INCX, Y, INCY) &
      bind(C, name='scopy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine scopy

    subroutine dcopy(N, X, INCX, Y, INCY) &
      bind(C, name='dcopy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dcopy

    subroutine ccopy(N, X, INCX, Y, INCY) &
      bind(C, name='ccopy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine ccopy

    subroutine zcopy(N, X, INCX, Y, INCY) &
      bind(C, name='zcopy$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zcopy

    real function sdot(N, X, INCX, Y, INCY) &
      bind(C, name='sdot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end function sdot

    double precision function ddot(N, X, INCX, Y, INCY) &
      bind(C, name='ddot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end function ddot

    subroutine cdotu(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='cdotu$NEWLAPACK$ILP64')
      complex, intent(inout) :: ret_val
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end subroutine cdotu

    subroutine zdotu(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='zdotu$NEWLAPACK$ILP64')
      double complex, intent(inout) :: ret_val
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zdotu

    subroutine cdotc(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='cdotc$NEWLAPACK$ILP64')
      complex, intent(inout) :: ret_val
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end subroutine cdotc

    subroutine zdotc(ret_val, N, X, INCX, Y, INCY) &
      bind(C, name='zdotc$NEWLAPACK$ILP64')
      double complex, intent(inout) :: ret_val
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zdotc

    real function sdsdot(N, ALPHA, X, INCX, Y, INCY) &
      bind(C, name='sdsdot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end function sdsdot

    double precision function dsdot(N, X, INCX, Y, INCY) &
      bind(C, name='dsdot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
    end function dsdot

    real function snrm2(N, X, INCX) &
      bind(C, name='snrm2$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function snrm2

    double precision function dnrm2(N, X, INCX) &
      bind(C, name='dnrm2$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function dnrm2

    real function scnrm2(N, X, INCX) &
      bind(C, name='scnrm2$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function scnrm2

    double precision function dznrm2(N, X, INCX) &
      bind(C, name='dznrm2$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
    end function dznrm2

    subroutine srot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='srot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      real, intent(in) :: C
      real, intent(in) :: S
    end subroutine srot

    subroutine drot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='drot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(in) :: C
      double precision, intent(in) :: S
    end subroutine drot

    subroutine csrot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='csrot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      real, intent(in) :: C
      real, intent(in) :: S
    end subroutine csrot

    subroutine zdrot(N, X, INCX, Y, INCY, C, S) &
      bind(C, name='zdrot$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(in) :: C
      double precision, intent(in) :: S
    end subroutine zdrot

    subroutine srotg(A, B, C, S) &
      bind(C, name='srotg$NEWLAPACK$ILP64')
      real, intent(inout) :: A
      real, intent(inout) :: B
      real, intent(inout) :: C
      real, intent(inout) :: S
    end subroutine srotg

    subroutine drotg(A, B, C, S) &
      bind(C, name='drotg$NEWLAPACK$ILP64')
      double precision, intent(inout) :: A
      double precision, intent(inout) :: B
      double precision, intent(inout) :: C
      double precision, intent(inout) :: S
    end subroutine drotg

    subroutine crotg(A, B, C, S) &
      bind(C, name='crotg$NEWLAPACK$ILP64')
      complex, intent(inout) :: A
      complex, intent(inout) :: B
      real, intent(inout) :: C
      complex, intent(inout) :: S
    end subroutine crotg

    subroutine zrotg(A, B, C, S) &
      bind(C, name='zrotg$NEWLAPACK$ILP64')
      double complex, intent(inout) :: A
      double complex, intent(inout) :: B
      double precision, intent(inout) :: C
      double complex, intent(inout) :: S
    end subroutine zrotg

    subroutine srotm(N, X, INCX, Y, INCY, PARAM) &
      bind(C, name='srotm$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      real, intent(in) :: PARAM
    end subroutine srotm

    subroutine drotm(N, X, INCX, Y, INCY, PARAM) &
      bind(C, name='drotm$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(in) :: PARAM
    end subroutine drotm

    subroutine srotmg(D1, D2, X1, Y1, PARAM) &
      bind(C, name='srotmg$NEWLAPACK$ILP64')
      real, intent(inout) :: D1
      real, intent(inout) :: D2
      real, intent(inout) :: X1
      real, intent(in) :: Y1
      real, intent(inout) :: PARAM
    end subroutine srotmg

    subroutine drotmg(D1, D2, X1, Y1, PARAM) &
      bind(C, name='drotmg$NEWLAPACK$ILP64')
      double precision, intent(inout) :: D1
      double precision, intent(inout) :: D2
      double precision, intent(inout) :: X1
      double precision, intent(in) :: Y1
      double precision, intent(inout) :: PARAM
    end subroutine drotmg

    subroutine sscal(N, ALPHA, X, INCX) &
      bind(C, name='sscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine sscal

    subroutine dscal(N, ALPHA, X, INCX) &
      bind(C, name='dscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dscal

    subroutine cscal(N, ALPHA, X, INCX) &
      bind(C, name='cscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine cscal

    subroutine zscal(N, ALPHA, X, INCX) &
      bind(C, name='zscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine zscal

    subroutine csscal(N, ALPHA, X, INCX) &
      bind(C, name='csscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine csscal

    subroutine zdscal(N, ALPHA, X, INCX) &
      bind(C, name='zdscal$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine zdscal

    subroutine sswap(N, X, INCX, Y, INCY) &
      bind(C, name='sswap$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine sswap

    subroutine dswap(N, X, INCX, Y, INCY) &
      bind(C, name='dswap$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dswap

    subroutine cswap(N, X, INCX, Y, INCY) &
      bind(C, name='cswap$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine cswap

    subroutine zswap(N, X, INCX, Y, INCY) &
      bind(C, name='zswap$NEWLAPACK$ILP64')
      integer(8), intent(in) :: N
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zswap

    subroutine sgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='sgemv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine sgemv

    subroutine dgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dgemv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dgemv

    subroutine cgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='cgemv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine cgemv

    subroutine zgemv(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zgemv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zgemv

    subroutine sgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='sgbmv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: KL
      integer(8), intent(in) :: KU
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine sgbmv

    subroutine dgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dgbmv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: KL
      integer(8), intent(in) :: KU
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dgbmv

    subroutine cgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='cgbmv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: KL
      integer(8), intent(in) :: KU
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine cgbmv

    subroutine zgbmv(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zgbmv$NEWLAPACK$ILP64')
      character, intent(in) :: TRANS
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: KL
      integer(8), intent(in) :: KU
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zgbmv

    subroutine sger(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='sger$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
      real, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine sger

    subroutine dger(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='dger$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine dger

    subroutine cgerc(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cgerc$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine cgerc

    subroutine zgerc(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zgerc$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine zgerc

    subroutine cgeru(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cgeru$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine cgeru

    subroutine zgeru(M, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zgeru$NEWLAPACK$ILP64')
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine zgeru

    subroutine chbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='chbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine chbmv

    subroutine zhbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zhbmv

    subroutine chemv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='chemv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine chemv

    subroutine zhemv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhemv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zhemv

    subroutine cher(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='cher$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine cher

    subroutine zher(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='zher$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine zher

    subroutine cher2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='cher2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine cher2

    subroutine zher2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='zher2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double complex, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine zher2

    subroutine chpmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='chpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: AP
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: BETA
      complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine chpmv

    subroutine zhpmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='zhpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: AP
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine zhpmv

    subroutine chpr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='chpr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(inout) :: AP
    end subroutine chpr

    subroutine zhpr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='zhpr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(inout) :: AP
    end subroutine zhpr

    subroutine chpr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='chpr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      complex, intent(inout) :: AP
    end subroutine chpr2

    subroutine zhpr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='zhpr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: X
      integer(8), intent(in) :: INCX
      double complex, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double complex, intent(inout) :: AP
    end subroutine zhpr2

    subroutine ssbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='ssbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine ssbmv

    subroutine dsbmv(UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dsbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dsbmv

    subroutine sspmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='sspmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: AP
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine sspmv

    subroutine dspmv(UPLO, N, ALPHA, AP, X, INCX, BETA, Y, INCY) &
      bind(C, name='dspmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: AP
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dspmv

    subroutine sspr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='sspr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: AP
    end subroutine sspr

    subroutine dspr(UPLO, N, ALPHA, X, INCX, AP) &
      bind(C, name='dspr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: AP
    end subroutine dspr

    subroutine sspr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='sspr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
      real, intent(inout) :: AP
    end subroutine sspr2

    subroutine dspr2(UPLO, N, ALPHA, X, INCX, Y, INCY, AP) &
      bind(C, name='dspr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(inout) :: AP
    end subroutine dspr2

    subroutine ssymv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='ssymv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: BETA
      real, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine ssymv

    subroutine dsymv(UPLO, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY) &
      bind(C, name='dsymv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: Y
      integer(8), intent(in) :: INCY
    end subroutine dsymv

    subroutine ssyr(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='ssyr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine ssyr

    subroutine dsyr(UPLO, N, ALPHA, X, INCX, A, LDA) &
      bind(C, name='dsyr$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine dsyr

    subroutine ssyr2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='ssyr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: X
      integer(8), intent(in) :: INCX
      real, intent(in) :: Y
      integer(8), intent(in) :: INCY
      real, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine ssyr2

    subroutine dsyr2(UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA) &
      bind(C, name='dsyr2$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: X
      integer(8), intent(in) :: INCX
      double precision, intent(in) :: Y
      integer(8), intent(in) :: INCY
      double precision, intent(inout) :: A
      integer(8), intent(in) :: LDA
    end subroutine dsyr2

    subroutine stbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='stbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine stbmv

    subroutine dtbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='dtbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtbmv

    subroutine ctbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ctbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctbmv

    subroutine ztbmv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ztbmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztbmv

    subroutine stbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='stbsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine stbsv

    subroutine dtbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='dtbsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtbsv

    subroutine ctbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ctbsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctbsv

    subroutine ztbsv(UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX) &
      bind(C, name='ztbsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztbsv

    subroutine stpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='stpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      real, intent(in) :: AP
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine stpmv

    subroutine dtpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='dtpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double precision, intent(in) :: AP
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtpmv

    subroutine ctpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ctpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      complex, intent(in) :: AP
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctpmv

    subroutine ztpmv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ztpmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double complex, intent(in) :: AP
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztpmv

    subroutine stpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='stpsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      real, intent(in) :: AP
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine stpsv

    subroutine dtpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='dtpsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double precision, intent(in) :: AP
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtpsv

    subroutine ctpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ctpsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      complex, intent(in) :: AP
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctpsv

    subroutine ztpsv(UPLO, TRANS, DIAG, N, AP, X, INCX) &
      bind(C, name='ztpsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double complex, intent(in) :: AP
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztpsv

    subroutine strmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='strmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine strmv

    subroutine dtrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='dtrmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtrmv

    subroutine ctrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ctrmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctrmv

    subroutine ztrmv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ztrmv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztrmv

    subroutine strsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='strsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine strsv

    subroutine dtrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='dtrsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine dtrsv

    subroutine ctrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ctrsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ctrsv

    subroutine ztrsv(UPLO, TRANS, DIAG, N, A, LDA, X, INCX) &
      bind(C, name='ztrsv$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      character, intent(in) :: DIAG
      integer(8), intent(in) :: N
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: X
      integer(8), intent(in) :: INCX
    end subroutine ztrsv

    subroutine sgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='sgemm$NEWLAPACK$ILP64')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: B
      integer(8), intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine sgemm

    subroutine dgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dgemm$NEWLAPACK$ILP64')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: B
      integer(8), intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine dgemm

    subroutine cgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='cgemm$NEWLAPACK$ILP64')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine cgemm

    subroutine zgemm(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zgemm$NEWLAPACK$ILP64')
      character, intent(in) :: TRANSA
      character, intent(in) :: TRANSB
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zgemm

    subroutine chemm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='chemm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine chemm

    subroutine zhemm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zhemm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zhemm

    subroutine cherk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='cherk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine cherk

    subroutine zherk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='zherk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zherk

    subroutine cher2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='cher2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      real, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine cher2k

    subroutine zher2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zher2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      double precision, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zher2k

    subroutine ssymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='ssymm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: B
      integer(8), intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine ssymm

    subroutine dsymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dsymm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: B
      integer(8), intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine dsymm

    subroutine csymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='csymm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine csymm

    subroutine zsymm(SIDE, UPLO, M, N, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zsymm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zsymm

    subroutine ssyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='ssyrk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine ssyrk

    subroutine dsyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='dsyrk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine dsyrk

    subroutine csyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='csyrk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine csyrk

    subroutine zsyrk(UPLO, TRANS, N, K, ALPHA, A, LDA, BETA, C, LDC) &
      bind(C, name='zsyrk$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zsyrk

    subroutine ssyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='ssyr2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(in) :: B
      integer(8), intent(in) :: LDB
      real, intent(in) :: BETA
      real, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine ssyr2k

    subroutine dsyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='dsyr2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(in) :: B
      integer(8), intent(in) :: LDB
      double precision, intent(in) :: BETA
      double precision, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine dsyr2k

    subroutine csyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='csyr2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      complex, intent(in) :: BETA
      complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine csyr2k

    subroutine zsyr2k(UPLO, TRANS, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) &
      bind(C, name='zsyr2k$NEWLAPACK$ILP64')
      character, intent(in) :: UPLO
      character, intent(in) :: TRANS
      integer(8), intent(in) :: N
      integer(8), intent(in) :: K
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(in) :: B
      integer(8), intent(in) :: LDB
      double complex, intent(in) :: BETA
      double complex, intent(inout) :: C
      integer(8), intent(in) :: LDC
    end subroutine zsyr2k

    subroutine strmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='strmm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine strmm

    subroutine dtrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='dtrmm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine dtrmm

    subroutine ctrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ctrmm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine ctrmm

    subroutine ztrmm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ztrmm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine ztrmm

    subroutine strsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='strsm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      real, intent(in) :: ALPHA
      real, intent(in) :: A
      integer(8), intent(in) :: LDA
      real, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine strsm

    subroutine dtrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='dtrsm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double precision, intent(in) :: ALPHA
      double precision, intent(in) :: A
      integer(8), intent(in) :: LDA
      double precision, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine dtrsm

    subroutine ctrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ctrsm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      complex, intent(in) :: ALPHA
      complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      complex, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine ctrsm

    subroutine ztrsm(SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB) &
      bind(C, name='ztrsm$NEWLAPACK$ILP64')
      character, intent(in) :: SIDE
      character, intent(in) :: UPLO
      character, intent(in) :: TRANSA
      character, intent(in) :: DIAG
      integer(8), intent(in) :: M
      integer(8), intent(in) :: N
      double complex, intent(in) :: ALPHA
      double complex, intent(in) :: A
      integer(8), intent(in) :: LDA
      double complex, intent(inout) :: B
      integer(8), intent(in) :: LDB
    end subroutine ztrsm

  end interface

end module accelerate_blas_ilp64
