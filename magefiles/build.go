//go:build mage

package main

import (
	"context"
	"fmt"
	"github.com/apigear-io/helper"
	"github.com/google/go-github/v48/github"
	"github.com/magefile/mage/sh"
	"log"
	"os"
	"runtime"
)

func autoPlatform() (string, string) {
	return runtime.GOOS, runtime.GOARCH
}

func apigear() string {
	if runtime.GOOS == "windows" {
		return "apigear.exe"
	}
	return "apigear"
}

func gitClone(url, dir string) {
	helper.Must(sh.RunV("git", "clone", "--depth=1", url, dir))
}


func goInstall(pkg string) {
	helper.Must(sh.RunV("go", "install", pkg))
}
func genSol(sol string) {
	bin := helper.Join("bin", apigear())
	helper.Must(sh.RunV(bin, "generate", "solution", sol))
}

// Install installs the apigear cli and testbed-apis.
func Install() error {
	log.Printf("install apigear %s %s", runtime.GOOS, runtime.GOARCH)
	err := helper.MkDir("tmp")
	if err != nil {
		return err
	}
	err = helper.MkDir("bin")
	if err != nil {
		return err
	}

	gh := github.NewClient(nil)
	release, _, err := gh.Repositories.GetLatestRelease(context.Background(), "apigear-io", "cli")
	if err != nil {
		return err
	}
	log.Printf("using latest release: %s", release.GetTagName())

	// asset name we are looking for
	asset := fmt.Sprintf("apigear_%s_%s.zip", runtime.GOOS, runtime.GOARCH)
	asset_url := fmt.Sprintf("https://github.com/apigear-io/cli/releases/latest/download/%s", asset)
	err = helper.HttpDownload(asset_url, "tmp/"+asset)
	if err != nil {
		return err
	}
	err = helper.ExtractZipFile("tmp/"+asset, "bin")
	if err != nil {
		return err
	}

	src := helper.Join("tmp", apigear())
	dst := helper.Join("bin", apigear())
	helper.Rename(src, dst)
	os.Chmod(dst, 0755)
	helper.RmDir("tmp")
	return nil
}

func GenerateAPI() {
	genSol("./apigear/performance.solution.yaml")
}

func GenerateMulitObjectAPI() {
	genSol("./apigear/performance100.solution.yaml")
}
