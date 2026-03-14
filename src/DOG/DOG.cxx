#include "DOGCLP.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main(int argc, char * argv[])
{
  PARSE_ARGS;

  if (sigma1 == sigma2)
  {
    std::cerr << "Error: We require that sigma1 != sigma2!" << std::endl;
    return EXIT_FAILURE;
  }

  if (sigma1 > sigma2)
  {
    std::cout << "Warning: Usually we want sigma2 > sigma1." << std::endl;
  }

  using InternalPixelType = float;
  constexpr unsigned int Dimension = 3;
  using InternalImageType = itk::Image<InternalPixelType, Dimension>;
  using OutputPixelType = unsigned char;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<InternalImageType>;
  using WriterType = itk::ImageFileWriter<OutputImageType>;
  using GaussianFilterType = itk::SmoothingRecursiveGaussianImageFilter<InternalImageType, InternalImageType>;
  using SubtractFilterType = itk::SubtractImageFilter<InternalImageType, InternalImageType, InternalImageType>;
  using RescaleFilterType = itk::RescaleIntensityImageFilter<InternalImageType, OutputImageType>;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputVolume);

  GaussianFilterType::Pointer filter1 = GaussianFilterType::New();
  filter1->SetInput(reader->GetOutput());
  filter1->SetSigma(sigma1);

  GaussianFilterType::Pointer filter2 = GaussianFilterType::New();
  filter2->SetInput(reader->GetOutput());
  filter2->SetSigma(sigma2);

  SubtractFilterType::Pointer subtractFilter = SubtractFilterType::New();
  subtractFilter->SetInput1(filter1->GetOutput());
  subtractFilter->SetInput2(filter2->GetOutput());

  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(subtractFilter->GetOutput());
  rescaleFilter->SetOutputMinimum(0);
  rescaleFilter->SetOutputMaximum(255);

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(rescaleFilter->GetOutput());

  try {
    writer->Update();
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "Exception: " << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}