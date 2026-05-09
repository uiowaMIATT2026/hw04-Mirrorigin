#include "GaussianLPFCLP.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRecursiveGaussianImageFilter.h"

int main(int argc, char * argv[])
{
  PARSE_ARGS;

  using PixelType = double;
  constexpr unsigned int Dimension = 3;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  using WriterType = itk::ImageFileWriter<ImageType>;
  using GaussianFilterType = itk::RecursiveGaussianImageFilter<ImageType, ImageType>;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName(inputVolume);
  writer->SetFileName(outputVolume);

  GaussianFilterType::Pointer filterX = GaussianFilterType::New();
  GaussianFilterType::Pointer filterY = GaussianFilterType::New();
  GaussianFilterType::Pointer filterZ = GaussianFilterType::New();

  filterX->SetDirection(0);
  filterY->SetDirection(1);
  filterZ->SetDirection(2);

  filterX->SetSigma(sigma);
  filterY->SetSigma(sigma);
  filterZ->SetSigma(sigma);

  // Reader -> X -> Y -> Z -> Writer
  filterX->SetInput(reader->GetOutput());
  filterY->SetInput(filterX->GetOutput());
  filterZ->SetInput(filterY->GetOutput());

  writer->SetInput(filterZ->GetOutput());

  try
  {
    writer->Update();
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "Exception caught during Gaussian filtering!" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}